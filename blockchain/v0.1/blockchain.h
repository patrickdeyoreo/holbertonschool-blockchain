#ifndef _BLOCKCHAIN_H_
#define _BLOCKCHAIN_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../../crypto/hblk_crypto.h"
#include "../../llist/llist.h"
#include "provided/endianness.h"

#define BLOCK_DATA_MAX_LEN 1024

/**
 * struct block_info_s - block info
 *
 * @index: index of the block in the blockchain
 * @difficulty: difficulty of proof of work (hash leading zero bits)
 * @timestamp: time the block was created at (UNIX timestamp)
 * @nonce: salt used to create the block hash
 * @prev_hash: hash of the previous block in the blockchain
 */
typedef struct block_info_s
{
	/*
	 * The order of the elements in this structure should remain the same.
	 * It was designed so every element of this structure is aligned and
	 * doesn't require padding from the compiler.
	 * Therefore, it is possible to use the structure as an array of char,
	 * on any architecture.
	 */
	uint32_t	index;
	uint32_t	difficulty;
	uint64_t	timestamp;
	uint64_t	nonce;
	uint8_t	prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;

/**
 * struct block_data_s - block data
 *
 * @buffer: data buffer
 * @len: data size (in bytes)
 */
typedef struct block_data_s
{
	/*
	 * @buffer must stay first, so we can directly use the structure as
	 * an array of char
	 */
	int8_t	buffer[BLOCK_DATA_MAX_LEN];
	uint32_t	len;
} block_data_t;

/**
 * struct block_s - block
 *
 * @info: block info
 * @data: block data
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */
typedef struct block_s
{
	block_info_t	info; /* this must stay first */
	block_data_t	data; /* this must stay second */
	uint8_t	hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
 * struct blockchain_s - blockchain
 *
 * @chain: linked list of pointers to block_t structures
 */
typedef struct blockchain_s
{
	llist_t	*chain;
} blockchain_t;

#endif /* _BLOCKCHAIN_H_ */
