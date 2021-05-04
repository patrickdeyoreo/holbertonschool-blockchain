#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

/**
 * cli_info - display information about the local blockchain
 *
 * @state: CLI state
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, return EXIT_SUCCESS.
 */
int cli_info(state_t *state)
{
	if (state->argc > 1)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	fprintf(stdout, "Blocks:  %d\n",
		llist_size(state->blockchain->chain));
	fprintf(stdout, "UTXOs:   %d\n",
		llist_size(state->blockchain->unspent));
	fprintf(stdout, "TX Pool: %d\n",
		llist_size(state->tx_pool));
	return ((state->status = EXIT_SUCCESS));
}
