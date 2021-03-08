#include "hblk_crypto.h"

/**
 * ec_create - create a new EC key pair
 *
 * Return: If an error occurs, return NULL. Otherwise, return a pointer to an
 * EC_KEY structure containing both the public and private keys.
 */
EC_KEY *ec_create(void)
{
	EC_KEY *key = EC_KEY_new_by_curve_name(EC_CURVE);

	if (key)
	{
		if (EC_KEY_generate_key(key))
			return (key);
		EC_KEY_free(key);
	}
	return (NULL);
}
