#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

/**
 * cli_help - display information about available commands
 *
 * @state: CLI state
 *
 * Return: If called with the wrong number of arguments, return 2.
 * Otherwise, return EXIT_SUCCESS.
 */
int cli_help(state_t *state)
{
	command_t const *command = NULL;

	if (state->argc > 2)
	{
		fprintf(stderr, "%s: too many arguments\n", state->argv[0]);
		return ((state->status = 2));
	}
	if (state->argc > 1)
	{
		command = find_command(state->argv[1]);
		if (command)
		{
			fprintf(stdout, "usage: %s\n%s\n",
				command->help, command->desc);
			return ((state->status = EXIT_SUCCESS));
		}
		fprintf(stderr, "%s: %s: command not found\n",
			state->argv[0], state->argv[1]);
		return ((state->status = EXIT_FAILURE));
	}
	command = get_commands();
	while (command->name)
	{
		fprintf(stdout, "%s\n", command->help);
		command += 1;
	}
	return ((state->status = EXIT_SUCCESS));
}
