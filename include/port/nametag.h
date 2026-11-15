#ifndef PORT_NAMETAG_H
#define PORT_NAMETAG_H

// Online name tags for the board status boxes: the player's name drawn where the game puts its
// "COM" tag, styled like it (white Rodin letters, dark outline).

#include <game/animdata.h>

#ifdef __cplusplus
extern "C" {
#endif

// Textures are drawn at this many texels per screen unit; draw the sprite at 1/scale.
#define PARTYBOARD_NAMETAG_SCALE 3

// A sprite animation (on HEAP_DATA, freed with the sprite) showing the online name of the player on
// `port`, or NULL if this isn't an online game, the port is a CPU, or the font can't be loaded.
ANIMDATA *partyboard_nametag_anim(int port);

#ifdef __cplusplus
}
#endif

#endif
