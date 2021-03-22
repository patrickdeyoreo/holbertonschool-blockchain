#include "blockchain.h"

/**
 * blockchain_destroy - destroy a blockchain
 *
 * @blockchain: pointer to the blockchain
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (blockchain)
	{
		node_dtor_t block_dtor = (void (*)(void *))block_destroy;
		llist_destroy(blockchain->chain, 1, block_dtor);
		blockchain->chain = NULL;
		free(blockchain);
	}
}
