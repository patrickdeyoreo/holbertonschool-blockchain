#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

/**
 * sum_unspent_amounts - count unspent transaction output amounts
 *
 * @node: unspent transaction output
 * @idx: node index
 * @arg: accumulator
 *
 * Return: Always 0
 */
static int sum_unspent_amounts(
	void *node, unsigned int idx __attribute__((unused)), void *arg)
{
	unspent_tx_out_t *unspent_tx_out = node;
	unsigned long int *accumulator = arg;

	*accumulator += unspent_tx_out->out.amount;

	return (0);
}

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
	unsigned long int coins = 0;

	if (state->argc > 1)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	llist_for_each(state->blockchain->unspent, sum_unspent_amounts, &coins);
	fprintf(stdout, "Blocks:  %d\n",
		llist_size(state->blockchain->chain));
	fprintf(stdout, "UTXOs:   %d\n",
		llist_size(state->blockchain->unspent));
	fprintf(stdout, "TX Pool: %d\n",
		llist_size(state->tx_pool));
	fprintf(stdout, "Coins:   %lu\n", coins);
	return ((state->status = EXIT_SUCCESS));
}
