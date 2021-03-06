/* sha256.h */
#ifndef _SHA256_H
#define _SHA256_H

#ifndef uint8
#define uint8 uint8_t
#endif

#ifndef uint32
#define uint32 uint32_t
#endif

typedef struct
{
	uint32 total[2];
	uint32 state[8];
	uint8 buffer[64];
}
sha256_context;


/** *************
* SHA256 Functions
** *************/
void sha256_starts( sha256_context *ctx );
void sha256_update( sha256_context *ctx, const uint8 *input, uint32 length );
void sha256_finish( sha256_context *ctx, uint8 digest[32] );

void hmac_sha256(const uint8_t *key, size_t keylen,const uint8_t *msg, size_t msglen,uint8_t res[32]);

#endif /* sha256.h */
