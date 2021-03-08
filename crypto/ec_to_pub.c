#include "hblk_crypto.h"

/**
 * ec_to_pub - extract the public key from an EC_KEY structure
 *
 * @key: pointer to the EC_KEY structure from which to extract the public key
 * @pub: address at which to store the extracted public key
 *
 * Description: If @key is NULL, nothing will be done.
 *
 * Return: If @key is NULL or an error occurs, return NULL.
 * Otherwise, return @pub.
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_GROUP *group = NULL;
	const EC_POINT *point = NULL;

	if (key)
	{
		group = EC_KEY_get0_group(key);
		point = EC_KEY_get0_public_key(key);

		if (group && point)
		{
			if (EC_POINT_point2oct(
					group, point,
					POINT_CONVERSION_UNCOMPRESSED,
					pub, EC_PUB_LEN, NULL))
			{
				return (pub);
			}
		}
	}
	return (NULL);
}
