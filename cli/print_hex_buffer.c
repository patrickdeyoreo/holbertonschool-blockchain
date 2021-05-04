#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * print_hex_buffer - print a buffer in its hexadecimal form
 *
 * @buf: Pointer to the buffer to be printed
 * @len: Number of bytes from @buf to be printed
 */
void print_hex_buffer(uint8_t const *buf, size_t len)
{
	size_t i;

	for (i = 0; buf && i < len; i++)
		printf("%02x", buf[i]);

	fflush(NULL);
}
