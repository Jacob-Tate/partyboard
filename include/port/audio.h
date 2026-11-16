#ifndef PORT_AUDIO_H_
#define PORT_AUDIO_H_

#include <dolphin/dvd.h>
#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

void partyboard_audio_lock(void);
void partyboard_audio_unlock(void);
void partyboard_audio_pre_init(void);
// Master volume, 0-100 %, from now on (Settings > Audio).
void partyboard_audio_set_master_volume(int percent);
void partyboard_audio_start(void);
void partyboard_audio_shutdown(void);
BOOL partyboard_audio_read_async(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset, DVDCallback callback);
// Frame-locked audio for deterministic runs: renders one game frame of audio. Call once per frame.
void partyboard_audio_frame(void);
int partyboard_audio_frame_locked(void);
// Drops queued stream reads and waits for the one in flight, so stream buffers can be freed. Call
// without holding the audio lock.
void partyboard_audio_drop_reads(void);

#ifdef __cplusplus
}
#endif

#endif
