#include "cli.h"

/**
 * state_clear - clear a CLI state structure
 *
 * @state: initialized CLI state
 */
void state_clear(state_t *state)
{
	state->argc = 0;
	free(state->argv);
	state->argv = NULL;
	free(state->line);
	state->line = NULL;
	state->linesz = 0;
	EC_KEY_free(state->wallet);
	state->wallet = NULL;
	blockchain_destroy(state->blockchain);
	state->blockchain = NULL;
	llist_destroy(state->tx_pool, 1, (node_dtor_t)transaction_destroy);
	state->tx_pool = NULL;
}
