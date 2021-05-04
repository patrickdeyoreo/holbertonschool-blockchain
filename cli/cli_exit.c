#include <stdio.h>
#include <stdlib.h>

#include "cli.h"

/**
 * cli_exit - exit
 *
 * @state: CLI state
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, if exit() fails, return EXIT_FAILURE.
 * Otherwise, do not return and exit with the status EXIT_SUCCESS.
 */
int cli_exit(state_t *state)
{
	if (state->argc > 1)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	free(state->line);
	state->line = NULL;
	state->linesz = 0;
	free(state->argv);
	state->argv = NULL;
	state->argc = 0;
	exit(EXIT_SUCCESS);
	return ((state->status = EXIT_FAILURE));
}
