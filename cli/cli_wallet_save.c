#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

/**
 * cli_wallet_save - save wallet to a file
 *
 * @state: CLI state
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, return EXIT_SUCCESS.
 */
int cli_wallet_save(state_t *state)
{
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
	if (!ec_save(state->wallet, state->argv[1]))
	{
		fprintf(stdout, "Failed to save wallet to %s\n",
			state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}
	fprintf(stdout, "Saved wallet to %s\n",
		state->argv[1]);
	return ((state->status = EXIT_SUCCESS));
}
