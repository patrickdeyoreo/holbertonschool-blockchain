#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

/**
 * cli_load - load blockchain from a file
 *
 * @state: CLI state
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, return EXIT_SUCCESS.
 */
int cli_load(state_t *state)
{
	blockchain_t *blockchain = NULL;

	if (state->argc > 2)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	if (state->argc < 2)
	{
		fprintf(stderr, "%s: too few arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	blockchain = blockchain_deserialize(state->argv[1]);
	if (!blockchain)
	{
		fprintf(stdout, "Failed to load blockchain from %s\n",
			state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}
	blockchain_destroy(state->blockchain);
	state->blockchain = blockchain;
	fprintf(stdout, "Loaded blockchain from %s\n",
		state->argv[1]);
	return ((state->status = EXIT_SUCCESS));
}
