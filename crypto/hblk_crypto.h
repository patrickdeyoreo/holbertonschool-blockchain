#ifndef _HBLK_CRYPTO_H_
#define _HBLK_CRYPTO_H_

#include <stddef.h>
#include <stdint.h>

#include <openssl/ec.h>
#include <openssl/sha.h>
#include <openssl/objects.h>

#define PRI_FILENAME	"key.pem"
#define PUB_FILENAME	"key_pub.pem"

#define EC_CURVE	NID_secp256k1

/* EC_KEY public key octet string length (using 256-bit curve) */
#define EC_PUB_LEN	65

/* maximum signature octet string length (using 256-bit curve) */
#define SIG_MAX_LEN	72

/**
 * struct sig_s - EC signature structure
 *
 * @sig: signature buffer (may be partially unused)
 * @len: signature size (must not exceed SIG_MAX_LEN)
 */
typedef struct sig_s
{
	uint8_t	sig[SIG_MAX_LEN];
	uint8_t	len;
} sig_t;

uint8_t *sha256(
	int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH]);

EC_KEY *ec_create(void);

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]);
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN]);

int ec_save(EC_KEY *key, char const *folder);
EC_KEY *ec_load(char const *folder);

uint8_t *ec_sign(
	EC_KEY const *key, uint8_t const *msg, size_t msglen, sig_t *sig);
int ec_verify(
	EC_KEY const *key, uint8_t const *msg, size_t msglen, sig_t const *sig);

void _print_hex_buffer(uint8_t const *buf, size_t len);

#endif /* _HBLK_CRYPTO_H_ */