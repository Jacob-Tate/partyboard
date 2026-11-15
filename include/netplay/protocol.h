#ifndef NETPLAY_PROTOCOL_H
#define NETPLAY_PROTOCOL_H

// Party Board netplay wire protocol, shared by the game client and the relay server.
//
// Transport: ENet (UDP). Channel 0 carries control messages, channel 1 carries inputs; both are
// reliable and ordered. Every packet starts with a one-byte message type, then the fields below
// in order, little-endian. Strings are a u8 length followed by that many bytes (no terminator).
//
// The server never runs game code: it relays controller input and compares checksums. Controller
// state is an opaque blob of the size the client announces in HELLO; every client in a room must
// run the same build (checked via build id), so the blob layout matches on all of them.

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PB_NET_PROTOCOL_VERSION 1
#define PB_NET_DEFAULT_PORT 7845
#define PB_NET_CHANNEL_CONTROL 0
#define PB_NET_CHANNEL_INPUT 1
#define PB_NET_CHANNEL_COUNT 2
#define PB_NET_MAX_PLAYERS 4
#define PB_NET_MAX_NAME 24
#define PB_NET_MAX_BUILD_ID 40
#define PB_NET_ROOM_CODE_LEN 4
#define PB_NET_MAX_PAD_SIZE 64
#define PB_NET_PORT_CPU 0xFF       // portOwner value for a CPU-controlled port
#define PB_NET_CHECKSUM_INTERVAL 60 // clients report a checksum every this many frames

typedef enum PbNetMsg {
    // client -> server
    PB_MSG_HELLO = 1,       // u16 protocol, str name, str buildId, u8 padSize
    PB_MSG_CREATE_ROOM = 2, // (empty)
    PB_MSG_JOIN_ROOM = 3,   // char code[4]
    PB_MSG_LEAVE_ROOM = 4,  // (empty)
    PB_MSG_START_GAME = 5,  // PbNetSettings (host only)
    PB_MSG_INPUT = 6,       // u32 frame, then u8 pad[padSize] for each port this client owns, in port order
    PB_MSG_CHECKSUM = 7,    // u32 frame, u32 hash

    // server -> client
    PB_MSG_WELCOME = 64,     // u8 clientId
    PB_MSG_ERROR = 65,       // u8 PbNetError, str message
    PB_MSG_ROOM_STATE = 66,  // char code[4], u8 hostId, u8 count, count x (u8 id, str name)
    PB_MSG_GAME_START = 67,  // PbNetSettings
    PB_MSG_FRAME = 68,       // u32 frame, u8 humanMask, for each set bit (port 0..3): u8 pad[padSize]
    PB_MSG_DESYNC = 69,      // u32 frame
    PB_MSG_GAME_ENDED = 70,  // u8 reason (PbNetEndReason), u8 clientId (who left, or 0xFF)
} PbNetMsg;

typedef enum PbNetError {
    PB_ERR_BAD_MESSAGE = 1,
    PB_ERR_VERSION = 2,     // protocol or build mismatch
    PB_ERR_NO_SUCH_ROOM = 3,
    PB_ERR_ROOM_FULL = 4,
    PB_ERR_IN_GAME = 5,     // room is already playing
    PB_ERR_NOT_HOST = 6,
    PB_ERR_BAD_SETTINGS = 7,
} PbNetError;

typedef enum PbNetEndReason {
    PB_END_PLAYER_LEFT = 1,
    PB_END_DESYNC = 2,
} PbNetEndReason;

// Everything every client needs to boot the same game. Serialized field by field.
typedef struct PbNetSettings {
    uint32_t seed;
    uint8_t board;      // 0-5
    uint8_t turns;      // 3-99 (the real game uses 10-50)
    uint8_t cpuLevel;   // 0-3
    uint8_t inputDelay; // frames between reading a pad and that input taking effect
    uint8_t chars[PB_NET_MAX_PLAYERS];     // character ids 0-7, all distinct
    uint8_t portOwner[PB_NET_MAX_PLAYERS]; // client id controlling each port, or PB_NET_PORT_CPU
} PbNetSettings;

// ---- Byte buffer helpers (bounds-checked) ----

typedef struct PbNetWriter {
    uint8_t *data;
    size_t size;
    size_t pos;
    int overflow;
} PbNetWriter;

typedef struct PbNetReader {
    const uint8_t *data;
    size_t size;
    size_t pos;
    int error;
} PbNetReader;

static inline void pbw_init(PbNetWriter *w, uint8_t *data, size_t size) {
    w->data = data; w->size = size; w->pos = 0; w->overflow = 0;
}
static inline void pbw_bytes(PbNetWriter *w, const void *src, size_t n) {
    if (w->overflow || w->pos + n > w->size) { w->overflow = 1; return; }
    memcpy(w->data + w->pos, src, n);
    w->pos += n;
}
static inline void pbw_u8(PbNetWriter *w, uint8_t v) { pbw_bytes(w, &v, 1); }
static inline void pbw_u16(PbNetWriter *w, uint16_t v) {
    uint8_t b[2] = { (uint8_t)v, (uint8_t)(v >> 8) };
    pbw_bytes(w, b, 2);
}
static inline void pbw_u32(PbNetWriter *w, uint32_t v) {
    uint8_t b[4] = { (uint8_t)v, (uint8_t)(v >> 8), (uint8_t)(v >> 16), (uint8_t)(v >> 24) };
    pbw_bytes(w, b, 4);
}
static inline void pbw_str(PbNetWriter *w, const char *s, size_t maxLen) {
    size_t n = s ? strlen(s) : 0;
    if (n > maxLen) n = maxLen;
    pbw_u8(w, (uint8_t)n);
    pbw_bytes(w, s, n);
}
static inline void pbw_settings(PbNetWriter *w, const PbNetSettings *s) {
    pbw_u32(w, s->seed);
    pbw_u8(w, s->board);
    pbw_u8(w, s->turns);
    pbw_u8(w, s->cpuLevel);
    pbw_u8(w, s->inputDelay);
    pbw_bytes(w, s->chars, PB_NET_MAX_PLAYERS);
    pbw_bytes(w, s->portOwner, PB_NET_MAX_PLAYERS);
}

static inline void pbr_init(PbNetReader *r, const uint8_t *data, size_t size) {
    r->data = data; r->size = size; r->pos = 0; r->error = 0;
}
static inline void pbr_bytes(PbNetReader *r, void *dst, size_t n) {
    if (r->error || r->pos + n > r->size) { r->error = 1; memset(dst, 0, n); return; }
    memcpy(dst, r->data + r->pos, n);
    r->pos += n;
}
static inline uint8_t pbr_u8(PbNetReader *r) { uint8_t v; pbr_bytes(r, &v, 1); return v; }
static inline uint16_t pbr_u16(PbNetReader *r) {
    uint8_t b[2]; pbr_bytes(r, b, 2);
    return (uint16_t)(b[0] | (b[1] << 8));
}
static inline uint32_t pbr_u32(PbNetReader *r) {
    uint8_t b[4]; pbr_bytes(r, b, 4);
    return (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}
// Reads a string into dst (capacity cap, always NUL-terminated); longer strings are an error.
static inline void pbr_str(PbNetReader *r, char *dst, size_t cap) {
    uint8_t n = pbr_u8(r);
    if (r->error || n >= cap) { r->error = 1; dst[0] = '\0'; return; }
    pbr_bytes(r, dst, n);
    dst[r->error ? 0 : n] = '\0';
}
static inline void pbr_settings(PbNetReader *r, PbNetSettings *s) {
    s->seed = pbr_u32(r);
    s->board = pbr_u8(r);
    s->turns = pbr_u8(r);
    s->cpuLevel = pbr_u8(r);
    s->inputDelay = pbr_u8(r);
    pbr_bytes(r, s->chars, PB_NET_MAX_PLAYERS);
    pbr_bytes(r, s->portOwner, PB_NET_MAX_PLAYERS);
}

// Validates settings the server will hand to every client.
static inline int pb_settings_valid(const PbNetSettings *s) {
    int i, j;
    if (s->board > 5 || s->turns < 3 || s->turns > 99 || s->cpuLevel > 3 || s->inputDelay > 30) {
        return 0;
    }
    for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
        if (s->chars[i] > 7) return 0;
        for (j = i + 1; j < PB_NET_MAX_PLAYERS; j++) {
            if (s->chars[i] == s->chars[j]) return 0;
        }
    }
    return 1;
}

#ifdef __cplusplus
}
#endif

#endif
