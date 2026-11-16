"""Mechanical MP5 -> MP4 renames for a ported REL source (decomp or tools/mp5/decomp.py output).
Usage: python tools/mp5/port.py <file.c> [DATADIR_MP5_xxx]
Leaves anything needing judgment (motions, sounds, char tables) for hand edits."""
import re, sys

path = sys.argv[1]
s = open(path, encoding='utf-8').read()

# GameCube REL loader glue
s = re.sub(r'typedef void \(\*VoidFunc\)\(void\);\s*extern const VoidFunc _ctors\[\];\s*extern const VoidFunc _dtors\[\];\s*', '', s)
s = re.sub(r'int _prolog\(void\)\s*\{.*?\n\}\s*\nvoid _epilog\(void\)\s*\{.*?\n\}\n', '', s, flags=re.S)

# an index that may itself hold one level of [] (GwPlayerConf[p->player[i].no])
IDX = r'\[((?:[^\[\]]|\[[^\[\]]*\])*)\]'
subs = [
    (r'->mdlId\b', '->model'), (r'->mtnId\b', '->motion'), (r'->objFunc\b', '->func'),
    (r'GwPlayerConf' + IDX + r'\.charNo', r'GWPlayerCfg[\1].character'),
    (r'GwPlayerConf' + IDX + r'\.padNo', r'GWPlayerCfg[\1].pad_idx'),
    (r'GwPlayerConf' + IDX + r'\.dif\b', r'GWPlayerCfg[\1].diff'),
    (r'GwPlayerConf' + IDX + r'\.type\b', r'GWPlayerCfg[\1].iscom'),
    (r'GwPlayerConf' + IDX + r'\.grp\b', r'GWPlayerCfg[\1].group'),
    (r'GwPlayer' + IDX + r'\.mgCoinBonus', r'GWPlayer[\1].coin_win'),
    (r'GwPlayer' + IDX + r'\.mgCoin\b', r'GWPlayer[\1].coin_win'),
    (r'_CheckFlag\(FLAG_MG_PRACTICE\)', '_CheckFlag(MP5_PRACTICE_FLAG)'),
    (r'_CheckFlag\(FLAG_INST_DECA\)', '0'),
    # m2c drafts use raw numbers
    (r'_CheckFlag\(0x1000FU?\)', '_CheckFlag(MP5_PRACTICE_FLAG)'),
    (r'_CheckFlag\(0x30002U?\)', '0'),
    (r'\bGameMesCreate\(2, 0(?:, [^)]*)?\)', 'MGSeqStartCreate()'),
    (r'\bGameMesCreate\(2, 1(?:, [^)]*)?\)', 'MGSeqFinishCreate()'),
    (r'\bGameMesCreate\(2, 2(?:, [^)]*)?\)', 'MGSeqDrawCreate()'),
    # (m2c may append leftover registers: GameMesCreate(4, 3, c, -1, -1, -1, (bitwise f32) x))
    (r'\bGameMesCreate\(4, 3, ([^,]+), ([^,]+), ([^,]+), ([^,)]+)(?:, [^;]*)?\);', r'MGSeqWinCreate(\1, \2, \3, \4);'),
    (r'(HuDataSelHeapReadNum\([^,]+), 0x10000000U?, HEAP_MODEL\)', r'\1, MEMORY_DEFAULT_NUM, HEAP_DATA)'),
    (r'HuMemDirectMallocNum\(HEAP_HEAP, ([^,]+), 0x10000000U?\)', r'HuMemDirectMallocNum(HEAP_SYSTEM, \1, MEMORY_DEFAULT_NUM)'),
    (r'\bPoint3d\b', 'Vec'),
    (r'\bPSVEC(\w+)\(', r'VEC\1('),
    (r'\bPSMTX(\w+)\(', r'MTX\1('),
    (r'\bOMOBJ\b', 'omObjData'),
    (r'Hu3DCameraPosGet\(', 'Mp5CameraPosGet('),
    (r'WipeCreate\(([^,]+), WIPE_TYPE_WHITEFADE, ', r'Mp5WipeWhite(\1, '),
    # m2c drafts: MP5 character motions by data number; DK (no MP5 motions) needs an MP4 motion picked by hand
    (r'\bCharMotionCreate\(([^,]+), ([^;]+)\);', r'Mp5CharMotionCreateData(\1, \2, 0 /* TODO(mp5): MP4 motion for DK */);'),
    # m2c drafts: print8(x, y, "fmt", scale, ...) -> MP4's print8(x, y, scale, "fmt", ...)
    (r'\bprint8\(([^,]+), ([^,]+), ("[^"]*"), ([^,)]+)', r'print8(\1, \2, \4, \3'),
    # HU3DPARMANPARAM: MP4 declares the second field as char[2]
    (r'(HU3DPARMANPARAM \w+ = \{\n\s*[^,\n]+,\n\s*)0,', r'\1{ 0 },'),
    # decathlon / story scores have no MP4 counterpart
    (r'\bGwPlayer\[.*?\]\.mgScore = [^;]*;', '/* MP5 decathlon score */'),
    # m2c drafts: MP5 wipe types by number (5 = PREVTYPE, 6 = WHITEFADE); MP4's enum differs
    (r'\bWipeCreate\(([^,]+), 5, ', r'WipeCreate(\1, WIPE_TYPE_NORMAL, '),
    (r'\bWipeCreate\(([^,]+), 6, ', r'Mp5WipeWhite(\1, '),
    # 0x81 = CROSSCOPY: MP5's cross-fade OUT only grabs the frame (one tick), its IN fades from it; MP4's
    # cross-fade does the same with an OUT of 1 frame (as w06's bowser.c uses it)
    (r'\bWipeCreate\((2|WIPE_MODE_OUT), (?:0x81|WIPE_TYPE_CROSSCOPY), [^;]*\);', r'WipeCreate(\1, WIPE_TYPE_CROSS, 1);'),
    (r'\bWipeCreate\((?:1|WIPE_MODE_IN), (?:0x81|WIPE_TYPE_CROSSCOPY), ', r'Mp5WipeCrossIn('),
    # MP5 code calls frandmod (u32) with a float in hand and no prototype, so it gets whatever r3 held; the
    # intent (a random start frame) is the float converted
    (r'\bfrandmod\(\(bitwise u32\) ', 'frandmod((u32) '),
    # memset has 3 arguments; m2c (no prototype in MP5's headers) appends leftover registers
    (r'\bmemset\(([^,;]+), ([^,;]+), ([^,;]+), [^;]+\);', r'memset(\1, \2, \3);'),
    # MgSeq calls that take no arguments: m2c passes whatever the registers held (MgSeqModeNext(&x))
    (r'\b(MgSeqModeNext|MgSeqKill|MgSeqModeGet|MgSeqModeChangeOff|MgSeqModeChangeOn|MgSeqDrawSet|MgSeqStatGet'
     r'|MgSeqFrameNoGet|MgSeqTimerValueGet|MgSeqGameMesIdGet)\([^()]+\)', r'\1()'),
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
        line = m.string[m.string.rfind(chr(10), 0, m.start()) + 1:m.start()]
        if re.search(r'Attr(?:Set|Reset)\(', line):  # model attribute bits (0x400000 ...), not a data number
            return m.group(0)
        used.add(_dirs[d].upper())
        if _dirs[d].upper() not in _mounted:
            return '0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_%s not mounted, entry %d */' % (_dirs[d].upper(), n)
        return 'DATA_MAKE_NUM(DATADIR_MP5_%s, %d)' % (_dirs[d].upper(), n)
    _pbt = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'include', 'datadir_table.h')
    _mounted = set(re.findall(r'DATADIR\(MP5_(\w+),', open(_pbt).read()))
    s = re.sub(r'\b0x([1-9A-E][0-9A-F]{5})U?\b', _num, s)
    if used:
        print('MP5 data dirs used (need DATADIR_MP5_* entries in datadir_table.h):', sorted(used))

# MP5 headers -> the shared compat header
s = re.sub(r'#include "(game/[a-z_/]+\.h|msm\.h|msm_stream\.h|math\.h|humath\.h)"\n', '', s)
s = re.sub(r'#include <(math\.h|humath\.h)>\n', '', s)
open(path, 'w', encoding='utf-8', newline='\n').write(s)
print('remaining MP5-isms:', sorted(set(re.findall(r'\b(GwPlayer\w*|GameMes\w*|MSM_\w+|CHARMOT_\w+|CHAR_HSF\w+|HuAudJinglePlay|M526_\w+|DATA_\w+)\b', s)))[:60])
