#ifndef PORT_MP5DISC_H
#define PORT_MP5DISC_H

// Optional second disc: Mario Party 5 (USA). Files the MP5 ports need (src/REL/m5xx*) are mounted
// read-only into the MP4 file system under /mp5/... (see the MP5_* entries in datadir_table.h), served
// straight from the user's own MP5 image. Without one, the MP5 minigames are simply unavailable.

#ifdef __cplusplus
extern "C" {
#endif

// Mounts the image at `path` (any format nod reads). Call after aurora_dvd_open. Returns 1 on success.
int partyboard_mp5_mount(const char *path);
// 1 when an MP5 disc is mounted.
int partyboard_mp5_available(void);
// Optional "DK in Mario Party 5" mod (OverBoo; DK in Boo's place): the extracted mod folder. Its teresa.bin and
// teresamot.bin are then mounted as /mp5dk/data/... and DK plays MP5's own animations in the ports instead of
// MP4 stand-ins. Call before partyboard_mp5_mount.
void partyboard_mp5_set_dk_mod(const char *dir);
// 1 when the DK mod is mounted and in use. Always 0 online: every machine must play the same animations.
int partyboard_mp5_dk_mod(void);

#ifdef __cplusplus
}
#endif

#endif
