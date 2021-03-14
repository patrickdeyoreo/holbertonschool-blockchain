#include "hblk_crypto.h"

/**
 * sha256 - compute the SHA-256 message digest of a sequence of bytes
 *
 * @s: pointer to the sequence of bytes to be hashed
 * @len: number of bytes in @s to be hashed
 * @digest: buffer in which to store the resulting message digest
 *
 * Description: If digest is not NULL, compute the SHA-256 message digest of
 * the first @len bytes in @s and store the result in @digest.
 *
 * Return: @digest
 */
uint8_t *sha256(
	int8_t const *s, size_t len, uint8_t digest[SHA256_DIGEST_LENGTH])
{
	return (s && digest ? SHA256((uint8_t const *)s, len, digest) : NULL);
}
