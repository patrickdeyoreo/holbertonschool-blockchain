#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

/**
 * cli_save - save blockchain to a file
 *
 * @state: CLI state
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, return EXIT_SUCCESS.
 */
int cli_save(state_t *state)
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
	if (blockchain_serialize(state->blockchain, state->argv[1]) == -1)
	{
		fprintf(stdout, "Failed to save blockchain to %s\n",
			state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}
	fprintf(stdout, "Saved blockchain to %s\n",
		state->argv[1]);
	return ((state->status = EXIT_SUCCESS));
}
