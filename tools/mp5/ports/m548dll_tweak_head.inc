#include "game/printfunc.h"
// ---- DK pose tweak panel (M548_TWEAK=1 builds only): Z toggles, D-pad up/down picks a value, left/right changes
// it (hold L for fine steps), X logs the values. The game (timer included) is frozen while the panel is open.
static int sDkTweak;
static int sDkMotReady; // set once the characters' motions exist
static int sDkSel;
static f32 sDkTw[9] = {
    0.0f, 0.0f, 0.0f, // right hand rotation X Y Z
    0.0f, 0.0f, 0.0f, // left hand rotation X Y Z
    20.0f,            // held head raise (all holds)
    12.0f,            // initial hold: head x
    12.0f,            // catch: head y
};
void Mp5DkTweak(omObjData *obj);
