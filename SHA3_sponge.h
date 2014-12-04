#ifndef SPONGE_H
#define SPONGE_H
// ** Thread-safe implementation
#include "Keccak512_data.h"

//Sponge modes:
#define SP_NORMAL 0
#define SP_DUPLEX 1
#define SP_ENCRYPT 1
#define SP_DECRYPT 3
#define SP_WRAP0 5
#define SP_WRAP1 0xD
#define SP_FORCE 0x10
#define SP_FORGET 0x31
#define SP_NOABS 0x40

//Original Keccak hashing (512bit hash)
extern int crypto_hash(BYTE *out, const BYTE *in, QWORD inlen );

//Duplex Sponge
extern void Sponge_init(KECCAK512_DATA *keccak, const BYTE *key, int klen, const BYTE *header, int hlen);
extern int Sponge_data(KECCAK512_DATA *keccak, const BYTE *buffer, int len, BYTE *output, char mode);
extern void Sponge_finalize(KECCAK512_DATA *keccak, BYTE *tag, int taglen);

extern void sponge_hmac_512(BYTE *tag, const BYTE *key, int keylen, const BYTE *in, int inlen );
#endif
