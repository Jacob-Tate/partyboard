#include "dolphin.h"

#ifdef TARGET_PC
#include <port/byteswap.h>
#endif

static void *MessData_MesDataGet(void *messdata, u32 id)
{
    s32 i;
    s32 max_bank;
    u16 *banks;
    u16 bank;
    s32 *data;
#ifdef TARGET_PC
    s32 ofs;
    u16 bank_pc;
#endif
    bank = id >> 16;
    data = messdata;
    max_bank = *data;
#ifdef TARGET_PC
    byteswap_s32(&max_bank);
#endif
    data++;
#ifdef TARGET_PC
    ofs = *data;
    byteswap_s32(&ofs);
    banks = (u16 *)(((u8 *)messdata) + ofs);
#else
    banks = (u16 *)(((u8 *)messdata)+(*data));
#endif
    for(i = max_bank; i != 0; i--, banks += 2) {
#ifdef TARGET_PC
        bank_pc = *banks;
        byteswap_u16(&bank_pc);
        if(bank_pc == bank) {
            break;
        }
#else
        if(*banks == bank) {
            break;
        }
#endif
    }
    if (i == 0) {
        return NULL;
    }
#ifdef TARGET_PC
    bank_pc = banks[1];
    byteswap_u16(&bank_pc);
    ofs = data[bank_pc];
    byteswap_s32(&ofs);
    return (((u8 *)messdata) + ofs);
#else
    data += banks[1];
    return (((u8 *)messdata) + (*data));
#endif
}

static void *_MessData_MesPtrGet(void *messbank, u32 id)
{
    u16 index;
    s32 max_index;
    s32 *data;
#ifdef TARGET_PC
    s32 ofs;
#endif

    index = id & 0xFFFF;
    data = messbank;
    max_index = *data;
#if TARGET_PC
    byteswap_s32(&max_index);
#endif
    data++;
    if(max_index <= index) {
        return NULL;
    } else {
        data =  data+index;
#ifdef TARGET_PC
        ofs = *data;
        byteswap_s32(&ofs);
        return (((u8 *)messbank)+(ofs));
#else
        return (((u8 *)messbank)+(*data));
#endif
    }
}

#ifdef TARGET_PC
void *partyboard_mp5_mess_get(u32 id);
#endif

void *MessData_MesPtrGet(void *messdata, u32 id)
{
#ifdef TARGET_PC
    if ((id >> 16) >= 0x100) { // MP5_MESS_BANK
        return partyboard_mp5_mess_get(id);
    }
#endif
    void *bank = MessData_MesDataGet(messdata, id);
    if(bank) {
        return _MessData_MesPtrGet(bank, id);
    }
    return NULL;
}
#ifdef TARGET_PC
#include "game/data.h"
#include "game/dvd.h"
#include "game/memory.h"
#include "port/mp5disc.h"
#include "port/mp5mess.h"
#include <stdlib.h>
#include <string.h>

// Mario Party 5's English text, for the MP5 minigame ports (port/mp5mess.h). messdata_eng.bin is big
// endian: u32 bankNum, u32 bankOfs[bankNum]; a bank at bankOfs + 4 is u32 num, u32 ofs[num] (from the
// bank + 4); a message is a 4-byte header, then its text in the same encoding as MP4's.
static u8 *mp5MessData;
static u32 mp5MessSize;
static struct {
    u32 id;
    u8 *text;
} mp5MessCache[256];
static s32 mp5MessCacheNum;

static u32 Mp5MessU32(u32 ofs)
{
    if (ofs + 4 > mp5MessSize) {
        return 0xFFFFFFFF;
    }
    return ((u32)mp5MessData[ofs] << 24) | ((u32)mp5MessData[ofs + 1] << 16) | ((u32)mp5MessData[ofs + 2] << 8)
        | mp5MessData[ofs + 3];
}

void *partyboard_mp5_mess_get(u32 id)
{
    u32 bank = (id >> 16) - MP5_MESS_BANK;
    u32 no = id & 0xFFFF;
    u32 base;
    u32 start;
    u32 end;
    u8 *text;
    s32 i;

    for (i = 0; i < mp5MessCacheNum; i++) {
        if (mp5MessCache[i].id == id) {
            return mp5MessCache[i].text;
        }
    }
    if (!mp5MessData) {
        void *data;
        if (!partyboard_mp5_available()) {
            return NULL;
        }
        data = HuDvdDataRead("mp5/mess/messdata_eng.bin");
        if (!data) {
            return NULL;
        }
        mp5MessSize = DirDataSize;
        mp5MessData = malloc(mp5MessSize);
        memcpy(mp5MessData, data, mp5MessSize);
        HuMemDirectFree(data);
    }
    if (bank >= Mp5MessU32(0)) {
        return NULL;
    }
    base = Mp5MessU32(4 + bank * 4) + 4;
    if (no >= Mp5MessU32(base)) {
        return NULL;
    }
    start = base + 4 + Mp5MessU32(base + 4 + no * 4) + 4;
    for (end = start; end < mp5MessSize && mp5MessData[end] != 0; end++) {
    }
    if (start > mp5MessSize || mp5MessCacheNum >= (s32)(sizeof(mp5MessCache) / sizeof(mp5MessCache[0]))) {
        return NULL;
    }
    // MP4 messages open with code 0x0B where MP5's have their header.
    text = malloc(end - start + 2);
    text[0] = 0x0B;
    memcpy(text + 1, mp5MessData + start, end - start);
    text[end - start + 1] = 0;
    mp5MessCache[mp5MessCacheNum].id = id;
    mp5MessCache[mp5MessCacheNum].text = text;
    mp5MessCacheNum++;
    return text;
}
#endif
