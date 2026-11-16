#ifndef PORT_MP5MESS_H
#define PORT_MP5MESS_H

// Mario Party 5's own English text (mess/messdata_eng.bin on the user's MP5 image, port/mp5disc.h), for the
// MP5 minigame ports' names and instructions. MP4's message calls take these ids like any other: banks
// from MP5_MESS_BANK up are MP5's message directories.

#define MP5_MESS_BANK 0x100
#define MP5_MESSID(dir, no) ((((MP5_MESS_BANK) + (dir)) << 16) + (no))

// MP5 message directories (its messdir_table.h, 0-based).
#define MP5_MESSDIR_MGINST 63
#define MP5_MESSDIR_MGNAME 67

// A minigame's name: MP5's MESS_MGNAME_M5xx.
#define MP5_MESS_MGNAME(mg) MP5_MESSID(MP5_MESSDIR_MGNAME, (mg) - 501)

#ifdef __cplusplus
extern "C" {
#endif

// The message `id` (an MP5_MESSID) converted to MP4's format, or NULL. Strings live until exit.
void *partyboard_mp5_mess_get(u32 id);

#ifdef __cplusplus
}
#endif

#endif
