#ifndef HASHBLOCK_H
#define HASHBLOCK_H

#include "uint256.h"
#include "sph_shavite.h"

#ifndef QT_NO_DEBUG
#include <string>
#endif

#ifdef GLOBALDEFINED
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL sph_shavite512_context     z_shavite;

#define fillz() do { \
    sph_shavite512_init(&z_shavite); \
} while (0) 

#define ZSHAVITE (memcpy(&ctx_shavite, &z_shavite, sizeof(z_shavite)))

template<typename T1>
inline uint256 Hashsea(const T1 pbegin, const T1 pend)

{
	sph_shavite512_context	 ctx_shavite;
    static unsigned char pblank[1];

#ifndef QT_NO_DEBUG
    //std::string strhash;
    //strhash = "";
#endif

       
    uint512 hash[2];

    sph_shavite512_init(&ctx_shavite);
    sph_shavite512 (&ctx_shavite, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[0]));
    
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[0]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[1]));

    return hash[1].trim256();
}







#endif // HASHBLOCK_H
