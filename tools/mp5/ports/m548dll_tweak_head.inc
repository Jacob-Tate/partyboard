#include "game/printfunc.h"
// ---- DK pose tweak panel (M548_TWEAK=1 builds only): Z toggles, D-pad up/down picks a value, left/right changes
// it (hold L for fine steps), X logs the values. The game (timer included) is frozen while the panel is open.
#define DKTW_N 20
static int sDkTweak;
static int sDkMotReady; // set once the characters' motions exist
static int sDkSel;
static f32 sDkTw[DKTW_N] = {
    125.0f, 0.0f, 0.0f, // 0-2 right hand rotation X Y Z
    0.0f, 0.0f, 0.0f,   // 3-5 left hand rotation X Y Z
    14.0f,              // 6 held head raise (all holds)
    32.0f,              // 7 initial hold: head x
    40.0f,              // 8 catch: head y
    -2.0f,              // 9 catch: head x
    0.0f, 0.0f, -35.0f, // 10-12 DK head rotation X Y Z (carry motion)
    0.0f, 0.0f, 0.0f,   // 13-15 both eyes: forward, up, spread (left +, right -)
    1.0f,               // 16 both eyes: size added to the scale (about 10.75)
    0.0f, 0.0f, 0.0f,   // 17-19 both eyes: rotation X Y Z
};
void Mp5DkTweak(omObjData *obj);
