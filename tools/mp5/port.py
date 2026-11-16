"""Mechanical MP5 -> MP4 renames for a ported REL source (decomp or tools/mp5/decomp.py output).
Usage: python tools/mp5/port.py <file.c> [DATADIR_MP5_xxx]
Leaves anything needing judgment (motions, sounds, char tables) for hand edits."""
import re, sys

path = sys.argv[1]
s = open(path, encoding='utf-8').read()

# GameCube REL loader glue
s = re.sub(r'typedef void \(\*VoidFunc\)\(void\);\s*extern const VoidFunc _ctors\[\];\s*extern const VoidFunc _dtors\[\];\s*', '', s)
s = re.sub(r'int _prolog\(void\)\s*\{.*?\n\}\s*\nvoid _epilog\(void\)\s*\{.*?\n\}\n', '', s, flags=re.S)

subs = [
    (r'->mdlId\b', '->model'), (r'->mtnId\b', '->motion'), (r'->objFunc\b', '->func'),
    (r'GwPlayerConf\[([^]]*)\]\.charNo', r'GWPlayerCfg[\1].character'),
    (r'GwPlayerConf\[([^]]*)\]\.padNo', r'GWPlayerCfg[\1].pad_idx'),
    (r'GwPlayerConf\[([^]]*)\]\.dif\b', r'GWPlayerCfg[\1].diff'),
    (r'GwPlayerConf\[([^]]*)\]\.type\b', r'GWPlayerCfg[\1].iscom'),
    (r'GwPlayerConf\[([^]]*)\]\.grp\b', r'GWPlayerCfg[\1].group'),
    (r'GwPlayer\[([^]]*)\]\.mgCoinBonus', r'GWPlayer[\1].coin_win'),
    (r'_CheckFlag\(FLAG_MG_PRACTICE\)', '_CheckFlag(MP5_PRACTICE_FLAG)'),
    (r'_CheckFlag\(FLAG_INST_DECA\)', '0'),
    (r'Hu3DCameraPosGet\(', 'Mp5CameraPosGet('),
    (r'WipeCreate\(([^,]+), WIPE_TYPE_WHITEFADE, ', r'Mp5WipeWhite(\1, '),
    (r'HuAudJinglePlay\(MSM_STREAM_JNGL_MG_WIN\)', 'HuAudSStreamPlay(MP5_JINGLE_WIN)'),
    (r'HuAudJinglePlay\(MSM_STREAM_JNGL_MG_DRAW\)', 'HuAudSStreamPlay(MP5_JINGLE_DRAW)'),
]
for a, b in subs:
    s = re.sub(a, b, s)
if len(sys.argv) > 2:
    s = re.sub(r'DATANUM\(DATA_\w+, (\d+)\)', r'DATA_MAKE_NUM(%s, \1)' % sys.argv[2], s)

# MP5 headers -> the shared compat header
s = re.sub(r'#include "(game/[a-z_/]+\.h|msm\.h|msm_stream\.h|math\.h|humath\.h)"\n', '', s)
s = re.sub(r'#include <(math\.h|humath\.h)>\n', '', s)
open(path, 'w', encoding='utf-8', newline='\n').write(s)
print('remaining MP5-isms:', sorted(set(re.findall(r'\b(GwPlayer\w*|GameMes\w*|MSM_\w+|CHARMOT_\w+|CHAR_HSF\w+|HuAudJinglePlay|M526_\w+|DATA_\w+)\b', s)))[:60])
