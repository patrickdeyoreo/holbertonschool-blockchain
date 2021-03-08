#include "hblk_crypto.h"

/**
 * ec_from_pub - create an EC_KEY structure given a public key
 *
 * @pub: address from which to read the public key
 *
 * Description: The private key of the created EC_KEY may be uninitialized.
 *
 * Return: If an error occurs, return NULL.
 * Otherwise, return a pointer to the created EC_KEY structure.
 */
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key = EC_KEY_new_by_curve_name(EC_CURVE);

	if (key)
	{
		if (EC_KEY_oct2key(key, pub, EC_PUB_LEN, NULL))
			return (key);
		EC_KEY_free(key);
	}
	return (NULL);
}
