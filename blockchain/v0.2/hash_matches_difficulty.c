#include "blockchain.h"

/**
 * get_difficulty - computers number of leading bits in hash
 *
 * @hash: hash buffer
 *
 * Return: computed difficulty
 */
static uint32_t compute_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH])
{
	uint8_t *ptr = (uint8_t *)hash;
	uint32_t difficulty = 0;
	int i;

	for (; ptr < hash + SHA256_DIGEST_LENGTH; ptr++)
	{
		for (i = 7; i >= 0; i--)
		{
			if ((*ptr >> i) & 1)
				return (difficulty);
			difficulty++;
		}
	}
	return (difficulty);
}

/**
 * hash_matches_difficulty - check if a given hash matches a given difficulty
 *
 * @hash: pointer to the hash to check
 * @difficulty: minimum difficulty the hash must match
 *
 * Return: If @difficulty is matched, return 1. Otherwise, return 0.
 */
int hash_matches_difficulty(
	uint8_t const hash[SHA256_DIGEST_LENGTH], uint32_t difficulty)
{
	return (hash ? compute_difficulty(hash) >= difficulty : 0);
}
