#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

/**
 * cli_wallet_load - load wallet from a file
 *
 * @state: CLI state
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, return EXIT_SUCCESS.
 */
int cli_wallet_load(state_t *state)
{
	EC_KEY *wallet = NULL;

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

	wallet = ec_load(state->argv[1]);
	if (!wallet)
	{
		fprintf(stdout, "Failed to load wallet from %s\n",
			state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}
	EC_KEY_free(state->wallet);
	state->wallet = wallet;
	fprintf(stdout, "Loaded wallet from %s\n",
		state->argv[1]);
	return ((state->status = EXIT_SUCCESS));
}
