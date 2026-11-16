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
    # m2c drafts use raw numbers
    (r'_CheckFlag\(0x1000FU?\)', '_CheckFlag(MP5_PRACTICE_FLAG)'),
    (r'_CheckFlag\(0x30002U?\)', '0'),
    (r'\bGameMesCreate\(2, 0(?:, [^)]*)?\)', 'MGSeqStartCreate()'),
    (r'\bGameMesCreate\(2, 1(?:, [^)]*)?\)', 'MGSeqFinishCreate()'),
    (r'\bGameMesCreate\(2, 2(?:, [^)]*)?\)', 'MGSeqDrawCreate()'),
    (r'\bGameMesCreate\(4, 3, ([^,]+), ([^,]+), ([^,]+), ([^,)]+)[^)]*\)', r'MGSeqWinCreate(\1, \2, \3, \4)'),
    (r'(HuDataSelHeapReadNum\([^,]+), 0x10000000U?, HEAP_MODEL\)', r'\1, MEMORY_DEFAULT_NUM, HEAP_DATA)'),
    (r'HuMemDirectMallocNum\(HEAP_HEAP, ([^,]+), 0x10000000U?\)', r'HuMemDirectMallocNum(HEAP_SYSTEM, \1, MEMORY_DEFAULT_NUM)'),
    (r'\bPoint3d\b', 'Vec'),
    (r'\bOMOBJ\b', 'omObjData'),
    (r'Hu3DCameraPosGet\(', 'Mp5CameraPosGet('),
    (r'WipeCreate\(([^,]+), WIPE_TYPE_WHITEFADE, ', r'Mp5WipeWhite(\1, '),
    # m2c drafts: MP5 wipe types by number (5 = PREVTYPE, 6 = WHITEFADE); MP4's enum differs
    (r'\bWipeCreate\(([^,]+), 5, ', r'WipeCreate(\1, WIPE_TYPE_NORMAL, '),
    (r'\bWipeCreate\(([^,]+), 6, ', r'Mp5WipeWhite(\1, '),
    (r'HuAudJinglePlay\(MSM_STREAM_JNGL_MG_WIN\)', 'HuAudSStreamPlay(MP5_JINGLE_WIN)'),
    (r'HuAudJinglePlay\(MSM_STREAM_JNGL_MG_DRAW\)', 'HuAudSStreamPlay(MP5_JINGLE_DRAW)'),
]
for a, b in subs:
    s = re.sub(a, b, s)
if len(sys.argv) > 2:
    s = re.sub(r'DATANUM\(DATA_\w+, (\d+)\)', r'DATA_MAKE_NUM(%s, \1)' % sys.argv[2], s)

# MP5 data numbers (0xDDNNNN, DD = MP5 datadir index) -> DATA_MAKE_NUM(DATADIR_MP5_<DIR>, N)
import os
_tbl = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..', 'mp5ref', 'include', 'datadir_table.h')
if os.path.exists(_tbl):
    _dirs = re.findall(r'DATADIR\((\w+)\)', open(_tbl).read())
    used = set()
    def _num(m):
        v = int(m.group(1), 16)
        d, n = v >> 16, v & 0xFFFF
        if d >= len(_dirs) or n > 0x200:
            return m.group(0)
        used.add(_dirs[d].upper())
        return 'DATA_MAKE_NUM(DATADIR_MP5_%s, %d)' % (_dirs[d].upper(), n)
    s = re.sub(r'\b0x([1-9A-E][0-9A-F]{5})U?\b', _num, s)
    if used:
        print('MP5 data dirs used (need DATADIR_MP5_* entries in datadir_table.h):', sorted(used))

# MP5 headers -> the shared compat header
s = re.sub(r'#include "(game/[a-z_/]+\.h|msm\.h|msm_stream\.h|math\.h|humath\.h)"\n', '', s)
s = re.sub(r'#include <(math\.h|humath\.h)>\n', '', s)
open(path, 'w', encoding='utf-8', newline='\n').write(s)
print('remaining MP5-isms:', sorted(set(re.findall(r'\b(GwPlayer\w*|GameMes\w*|MSM_\w+|CHARMOT_\w+|CHAR_HSF\w+|HuAudJinglePlay|M526_\w+|DATA_\w+)\b', s)))[:60])
