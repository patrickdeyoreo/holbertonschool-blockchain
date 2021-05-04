#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

/**
 * cli_mine - mine a block
 *
 * @state: CLI state
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, return EXIT_SUCCESS.
 */
int cli_mine(state_t *state)
{
	if (state->argc > 1)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	return ((state->status = EXIT_SUCCESS));
}