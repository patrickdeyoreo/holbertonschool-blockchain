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
	const EC_GROUP *group = NULL;
	EC_POINT *point = NULL;
	EC_KEY *key = EC_KEY_new_by_curve_name(EC_CURVE);

	if (key)
	{
		group = EC_KEY_get0_group(key);

		if (group)
		{
			point = EC_POINT_new(group);

			if (point)
			{
				if (EC_POINT_oct2point(
						group, point,
						pub, EC_PUB_LEN, NULL) &&
					EC_KEY_set_public_key(key, point))
				{
					EC_POINT_free(point);
					return (key);
				}
				EC_POINT_free(point);
			}
		}
		EC_KEY_free(key);
	}
	return (NULL);
}
