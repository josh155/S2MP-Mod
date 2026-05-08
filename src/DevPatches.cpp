/////////////////////////////////////////////////
//         Development Patches
// Temporary patches for testing stuff
/////////////////////////////////////////////////

#include "pch.h"
#include "DevPatches.hpp"
#include "Console.hpp"
#include "FuncPointers.h"
#include "GameUtil.hpp"
#include "ImageLoader.hpp"
#include "memory.h"
#include <DevDef.h>
#include <xsk/gsc/engine/s2.hpp>
#include <Hook.hpp>
#include <string.h>
#include "DvarInterface.hpp"

typedef void* (*BG_GetWorldModel_t)(Weapon* weapon, bool isAlternate, int variation);
static BG_GetWorldModel_t fpBG_GetWorldModel;

//force missing world models to use defaultweapon to prevent error 560
void* BG_GetWorldModel_hookfunc(Weapon* weapon, bool isAlternate, int variation) {
    void* model = fpBG_GetWorldModel(weapon, isAlternate, variation);
    if (!model) {
        model = Functions::_DB_FindXAssetHeader(ASSET_TYPE_XMODEL, "defaultweapon", 1).data;
    }
    return model;
}


typedef int (*Crypto_TransformBufferInPlace_t)(int ivSeed, uint8_t* buffer, uint32_t size);
static Crypto_TransformBufferInPlace_t fpCrypto_TransformBufferInPlace;

int Crypto_TransformBufferInPlace_hookfunc(int ivSeed, unsigned char* buffer, unsigned int size)
{
    DEV_PRINTF(
        "[CFG_CRYPTO] BEFORE ivSeed=0x%08X size=%u buffer=%p first32=%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
        ivSeed,
        size,
        buffer,
        buffer ? buffer[0] : 0, buffer ? buffer[1] : 0, buffer ? buffer[2] : 0, buffer ? buffer[3] : 0,
        buffer ? buffer[4] : 0, buffer ? buffer[5] : 0, buffer ? buffer[6] : 0, buffer ? buffer[7] : 0,
        buffer ? buffer[8] : 0, buffer ? buffer[9] : 0, buffer ? buffer[10] : 0, buffer ? buffer[11] : 0,
        buffer ? buffer[12] : 0, buffer ? buffer[13] : 0, buffer ? buffer[14] : 0, buffer ? buffer[15] : 0,
        buffer ? buffer[16] : 0, buffer ? buffer[17] : 0, buffer ? buffer[18] : 0, buffer ? buffer[19] : 0,
        buffer ? buffer[20] : 0, buffer ? buffer[21] : 0, buffer ? buffer[22] : 0, buffer ? buffer[23] : 0,
        buffer ? buffer[24] : 0, buffer ? buffer[25] : 0, buffer ? buffer[26] : 0, buffer ? buffer[27] : 0,
        buffer ? buffer[28] : 0, buffer ? buffer[29] : 0, buffer ? buffer[30] : 0, buffer ? buffer[31] : 0
    );

    int result = fpCrypto_TransformBufferInPlace(ivSeed, buffer, size);

    DEV_PRINTF(
        "[CFG_CRYPTO] AFTER result=%d ivSeed=0x%08X size=%u buffer=%p first32=%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
        result,
        ivSeed,
        size,
        buffer,
        buffer ? buffer[0] : 0, buffer ? buffer[1] : 0, buffer ? buffer[2] : 0, buffer ? buffer[3] : 0,
        buffer ? buffer[4] : 0, buffer ? buffer[5] : 0, buffer ? buffer[6] : 0, buffer ? buffer[7] : 0,
        buffer ? buffer[8] : 0, buffer ? buffer[9] : 0, buffer ? buffer[10] : 0, buffer ? buffer[11] : 0,
        buffer ? buffer[12] : 0, buffer ? buffer[13] : 0, buffer ? buffer[14] : 0, buffer ? buffer[15] : 0,
        buffer ? buffer[16] : 0, buffer ? buffer[17] : 0, buffer ? buffer[18] : 0, buffer ? buffer[19] : 0,
        buffer ? buffer[20] : 0, buffer ? buffer[21] : 0, buffer ? buffer[22] : 0, buffer ? buffer[23] : 0,
        buffer ? buffer[24] : 0, buffer ? buffer[25] : 0, buffer ? buffer[26] : 0, buffer ? buffer[27] : 0,
        buffer ? buffer[28] : 0, buffer ? buffer[29] : 0, buffer ? buffer[30] : 0, buffer ? buffer[31] : 0
    );

    return result;
}

struct symmetric_key
{
    uint32_t eK[60];
    uint32_t dK[60];
    int Nr;
};

struct symmetric_CTR
{
    int cipher;
    int blocklen;
    int padlen;
    int mode;
    uint8_t ctr[128];
    uint8_t pad[128];
    symmetric_key key;
};

typedef int (*ctr_setiv_t)(const unsigned __int8* IV, unsigned int len, symmetric_CTR* ctr);
static ctr_setiv_t fpctr_setiv;

int ctr_setiv_hookfunc(const unsigned __int8* IV, unsigned int len, symmetric_CTR* ctr)
{
    bool repeated = false;
    unsigned int d0 = 0, d1 = 0, d2 = 0, d3 = 0;

    if (IV && len == 16)
    {
        memcpy(&d0, IV + 0, 4);
        memcpy(&d1, IV + 4, 4);
        memcpy(&d2, IV + 8, 4);
        memcpy(&d3, IV + 12, 4);

        repeated = (d0 == d1 && d1 == d2 && d2 == d3);
    }

    int result = fpctr_setiv(IV, len, ctr);

    // Only print the call we care about.
    if (repeated)
    {
        int cipher = ctr ? *(int*)((char*)ctr + 0x00) : -1;
        int blocklen = ctr ? *(int*)((char*)ctr + 0x04) : -1;
        int padlen = ctr ? *(int*)((char*)ctr + 0x08) : -1;
        int mode = ctr ? *(int*)((char*)ctr + 0x0C) : -1;

        DEV_PRINTF(
            "[ctr_setiv:REPEATED] ctr=%p result=%d seed=0x%08X IV_HEX=%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X cipher=%d blocklen=%d padlen=%d mode=%d",
            ctr,
            result,
            d0,
            IV[0], IV[1], IV[2], IV[3],
            IV[4], IV[5], IV[6], IV[7],
            IV[8], IV[9], IV[10], IV[11],
            IV[12], IV[13], IV[14], IV[15],
            cipher,
            blocklen,
            padlen,
            mode
        );
    }

    return result;
}

typedef int (*ctr_start_t)(int cipher, const unsigned __int8* IV, const unsigned __int8* key, unsigned int keylen, unsigned int num_rounds, int ctr_mode, void* ctr);
static ctr_start_t fpctr_start;

int ctr_start_hookfunc(int cipher, const unsigned __int8* IV, const unsigned __int8* key, unsigned int keylen, unsigned int num_rounds, int ctr_mode, void* ctr) {
    int result = fpctr_start(cipher, IV, key, keylen, num_rounds, ctr_mode, ctr);

    // Log only normal AES-192/AES-256 candidates and avoid the super-hot global ctx if desired.
    if (result == 0 && key && (keylen == 24 || keylen == 32))
    {
        char keyHex[128] = {};
        unsigned int pos = 0;

        for (unsigned int i = 0; i < keylen && pos + 3 < sizeof(keyHex); ++i)
            pos += snprintf(keyHex + pos, sizeof(keyHex) - pos, "%02X", key[i]);

        DEV_PRINTF(
            "[ctr_start:CANDIDATE] ctr=%p cipher=%d keylen=%u mode=%d key=%s",
            ctr,
            cipher,
            keylen,
            ctr_mode,
            keyHex
        );
    }

    return result;
}

void DevPatches::init()  {
    DEV_INIT_PRINT();
    //make weapons without world models work
    Hook::create("BG_GetWorldModel", 0x3BCD30_b, &BG_GetWorldModel_hookfunc, &fpBG_GetWorldModel);


   //
   // Hook::create("Crypto_TransformBufferInPlace", 0x15DC0_b, &Crypto_TransformBufferInPlace_hookfunc, &fpCrypto_TransformBufferInPlace);
   // Hook::create("ctr_setiv", 0x92BD90_b, &ctr_setiv_hookfunc, &fpctr_setiv);
   // Hook::create("ctr_start", 0x92BAB0_b, &ctr_start_hookfunc, &fpctr_start);
}
