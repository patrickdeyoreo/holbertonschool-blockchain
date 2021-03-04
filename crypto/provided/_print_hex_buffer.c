#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * _print_hex_buffer - print a hexadecimal representation of a buffer
 *
 * @buf: pointer to the buffer to be printed
 * @len: number of bytes to be printed
 */
void _print_hex_buffer(uint8_t const *buf, size_t len)
{
	if (buf)
	{
		while (len--)
			printf("%02x", *buf++);
	}
}
