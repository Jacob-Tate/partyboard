#ifndef PORT_TOUCH_PAD_H
#define PORT_TOUCH_PAD_H

/*
 * Party Board has no on-screen touch pad. The button icon code (port/button_icons.cpp, from the FIZL0/partyboard
 * fork) asks whether one is shown to pick its touch glyphs; it never is here.
 */

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline bool touch_pad_shown(void) { return false; }
static inline int touch_pad_port(void) { return -1; }

#ifdef __cplusplus
}
#endif

#endif
