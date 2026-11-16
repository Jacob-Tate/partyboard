#ifndef PORT_INPUTSYNC_H
#define PORT_INPUTSYNC_H

// Controller input source for the game: live pads, a recording, or an online game (port/netplay.h).
//
//   --record <file>   Save the game settings and every controller read (needs --quickstart --seed)
//   --replay <file>   Play a recording back instead of reading the controllers; quits at the end

#include <dolphin/pad.h>

#ifdef __cplusplus
extern "C" {
#endif

// Returns 0 on a bad option or unreadable file.
int partyboard_input_open(const char *recordPath, const char *replayPath);
// Drop-in replacement for PADRead() in the game's per-frame controller poll.
u32 partyboard_input_pad_read(PADStatus *status);
// True when input must not come from local-only sources (soft reset combo, etc.).
int partyboard_input_is_synced(void);
// PADControlMotor for the game: online, a seat's rumble goes to the local controller that plays it.
void partyboard_input_control_motor(s32 chan, u32 command);
void partyboard_input_close(void);

#ifdef __cplusplus
}
#endif

#endif
