#ifndef _GAME_AUDIO_H
#define _GAME_AUDIO_H

#include "dolphin.h"
#include "game/msm_grpset.h"
#include "version.h"

typedef struct sndGrpTbl_s {
    s16 ovl;
    s16 grpSet;
    s32 auxANo;
    s32 auxBNo;
    s8 auxAVol;
    s8 auxBVol;
} SNDGRPTBL;


void HuAudInit(void);
s32 HuAudStreamPlay(char *name, BOOL flag);
void HuAudStreamVolSet(s16 vol);
void HuAudStreamPauseOn(void);
void HuAudStreamPauseOff(void);
void HuAudStreamFadeOut(s32 streamNo);
void HuAudAllStop(void);
void HuAudFadeOut(s32 speed);
int HuAudFXPlay(int seId);
int HuAudFXPlayVol(int seId, s16 vol);
int HuAudFXPlayVolPan(int seId, s16 vol, s16 pan);
void HuAudFXStop(int seNo);
void HuAudFXAllStop(void);
void HuAudFXFadeOut(int seNo, s32 speed);
void HuAudFXPanning(int seNo, s16 pan);
void HuAudFXListnerSet(Vec *pos, Vec *heading, float sndDist, float sndSpeed);
void HuAudFXListnerSetEX(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis);
void HuAudFXListnerUpdate(Vec *pos, Vec *heading);
int HuAudFXEmiterPlay(int seId, Vec *pos);
void HuAudFXEmiterUpDate(int seNo, Vec *pos);
void HuAudFXListnerKill(void);
void HuAudFXPauseAll(BOOL pauseF);
s32 HuAudFXStatusGet(int seNo);
s32 HuAudFXPitchSet(int seNo, s16 pitch);
s32 HuAudFXVolSet(int seNo, s16 vol);
s32 HuAudSeqPlay(s16 musId);
void HuAudSeqStop(s32 musNo);
void HuAudSeqFadeOut(s32 musNo, s32 speed);
void HuAudSeqAllFadeOut(s32 speed);
void HuAudSeqAllStop(void);
void HuAudSeqPauseAll(BOOL pause);
void HuAudSeqPause(s32 musNo, s32 pause, s32 speed);
s32 HuAudSeqMidiCtrlGet(s32 musNo, s8 channel, s8 ctrl);
s32 HuAudSStreamPlay(s16 streamId);
void HuAudSStreamStop(s32 seNo);
void HuAudSStreamFadeOut(s32 seNo, s32 speed);
void HuAudSStreamAllFadeOut(s32 speed);
void HuAudSStreamAllStop(void);
s32 HuAudSStreamStatGet(s32 seNo);
void HuAudDllSndGrpSet(u16 ovl);
void HuAudSndGrpSetSet(s16 grpSet);
void HuAudSndGrpSet(s16 grpId);
void HuAudSndCommonGrpSet(s16 grp, BOOL delGrpF);
void HuAudAUXSet(s32 auxA, s32 auxB);
void HuAudAUXVolSet(s8 volA, s8 volB);
void HuAudSndCharGrpSet(s16 ovl);
s32 PlayerFXPlay(s16 player, s16 seId);
s32 PlayerFXPlayPos(s16 player, s16 seId, Vec *pos);
void PlayerFXStop(s16 player, s16 seId);
s32 CharFXPlay(s16 charNo, s16 seId);
s32 CharFXPlayPos(s16 charNo, s16 seId, Vec *pos);
void CharFXStop(s16 charNo, s16 seId);

#ifdef TARGET_PC
// Mario Party 5's own sound bank, loaded while an MP5 minigame port runs (see audio.c). These take MP5's
// sound ids, as the MP5 decompilation writes them, and play them untranslated. CharFX ids are relative to
// Mario's (MSM_SE_MARIO / MSM_SE_VOICE_MARIO), as in MP5.
BOOL HuAudMp5BankActive(void);
int HuAudMp5FXPlay(int seId);
int HuAudMp5FXPlayVol(int seId, s16 vol);
int HuAudMp5FXPlayPan(int seId, s16 pan);
int HuAudMp5FXPlayVolPan(int seId, s16 vol, s16 pan);
int HuAudMp5FXEmiterPlay(int seId, Vec *pos);
s32 HuAudMp5CharFXPlayVolPan(s16 charNo, s16 seId, s16 vol, s16 pan);
s32 HuAudMp5CharFXPlayPos(s16 charNo, s16 seId, Vec *pos);
void HuAudMp5CharFXStop(s16 charNo, s16 seId);
#endif

SHARED_SYM extern SNDGRPTBL sndGrpTable[];

extern float Snd3DBackSurDisOffset;
extern float Snd3DFrontSurDisOffset;
extern float Snd3DStartDisOffset;
extern float Snd3DSpeedOffset;
extern float Snd3DDistOffset;
extern BOOL musicOffF;
extern u8 fadeStat;

#endif
