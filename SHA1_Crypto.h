/*hmac_sha1.h*/

#ifndef SHA1_CRYPTO_H_
#define SHA1_CRYPTO_H_

#define HMAC_TAG_20BYTES	20

typedef struct{
	uint32_t state[5];
	uint32_t count[2];
	uint8_t buffer[64];
} SHA1_CTX;


/** *************
* SHA1 Functions
** *************/

void SHA1Transform(uint32_t state[5], const uint8_t buffer[64]);
void SHA1Init(SHA1_CTX* context);
void SHA1Update(SHA1_CTX* context, const uint8_t* data, unsigned int len);
void SHA1Final(uint8_t digest[20], SHA1_CTX* context);

/*
unsigned char*  text;                pointer to data stream
int             text_len;            length of data stream
unsigned char*  key;                 pointer to authentication key
int             key_len;             length of authentication key
unsigned char*  digest;              caller digest to be filled in
*/
void hmac_sha1(const unsigned char* text, int text_len, const unsigned char* key, int key_len, unsigned char *digest);

#endif
