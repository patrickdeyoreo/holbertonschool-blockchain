#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

/**
 * _cli_send - send coins (helper function)
 *
 * @state: CLI state
 * @amount: amount to send
 * @pub: public key of receiver
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, return EXIT_SUCCESS.
 */
static int _cli_send(state_t *state, uint32_t amount, uint8_t pub[EC_PUB_LEN])
{
	EC_KEY *receiver = NULL;
	transaction_t *tx = NULL;

	receiver = ec_from_pub(pub);
	if (!receiver)
	{
		fprintf(stderr, "%s: %s: invalid receiver public key\n",
			state->argv[0], state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}
	tx = transaction_create(
		state->wallet, receiver, amount, state->blockchain->unspent);
	if (!tx)
	{
		fprintf(stderr, "%s: failed to create transaction\n",
			state->argv[0]);
		EC_KEY_free(receiver);
		return ((state->status = EXIT_FAILURE));
	}
	if (!transaction_is_valid(tx, state->blockchain->unspent))
	{
		fprintf(stderr, "%s: invalid transaction\n",
			state->argv[0]);
		EC_KEY_free(receiver);
		transaction_destroy(tx);
		return ((state->status = EXIT_FAILURE));
	}
	if (llist_add_node(state->tx_pool, tx, ADD_NODE_REAR) == -1)
	{
		fprintf(stdout, "Failed to add transaction to local transaction pool\n");
		EC_KEY_free(receiver);
		transaction_destroy(tx);
		return ((state->status = EXIT_FAILURE));
	}
	fprintf(stdout, "Transaction added to local transaction pool\n");
	EC_KEY_free(receiver);
	return ((state->status = EXIT_SUCCESS));
}

/**
 * cli_send - send coins
 *
 * @state: CLI state
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, return EXIT_SUCCESS.
 */
int cli_send(state_t *state)
{
	uint8_t pub[EC_PUB_LEN] = {0};
	size_t pub_index = 0;
	unsigned long int amount = 0;
	int nmatched = 0;
	char *endptr = NULL;

	if (state->argc > 3)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	if (state->argc < 3)
	{
		fprintf(stderr, "%s: too few arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	errno = 0;
	amount = strtoul(state->argv[1], &endptr, 0);
	if ((errno != 0 && (amount == 0 || amount == ULONG_MAX)) ||
		(*state->argv[1] == '\0' || *endptr != '\0') ||
		(amount > UINT32_MAX))
	{
		fprintf(stderr, "%s: %s: invalid amount\n",
			state->argv[0], state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}
	while (pub_index < EC_PUB_LEN)
	{
		nmatched = sscanf(
			(state->argv[2] + (2 * pub_index)), "%02x",
			(unsigned int *)(pub + pub_index));
		if (nmatched == 0)
			break;
		pub_index += 1;
	}
	return (_cli_send(state, amount, pub));
}
