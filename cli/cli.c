#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cli.h"

/**
 * dispatch - dispatch a command by calling the associated function
 *
 * @state: CLI state
 *
 * Return: If an error occurs or the command does not exist, return -1.
 * Otherwise, return the exit status of the executed command.
 */
static int dispatch(state_t *state)
{
	command_t const *command = get_commands();

	while (command->name)
	{
		if (strcmp(state->argv[0], command->name) == 0)
			return (command->func(state));
		command += 1;
	}
	fprintf(stderr, "%s: command not found\n", state->argv[0]);
	return (-1);
}

/**
 * tokenize - tokenize a line
 *
 * @state: CLI state
 */
static void tokenize(state_t *state)
{
	char *linedup = strdup(state->line);
	char **tokens = NULL;
	char *token = NULL;
	int ntokens = 0;

	state->argc = 0;
	state->argv = NULL;
	if (linedup)
	{
		token = strtok(linedup, BLANK);
		if (token)
		{
			do {
				ntokens += 1;
				token = strtok(NULL, BLANK);
			} while (token);
		}
		tokens = calloc(ntokens + 1, sizeof(*tokens));
		ntokens = 0;
		token = strtok(state->line, BLANK);
		if (token)
		{
			do {
				tokens[ntokens] = token;
				ntokens += 1;
				token = strtok(NULL, BLANK);
			} while (token);
		}
		state->argc = ntokens;
		state->argv = tokens;
	}
}

/**
 * main - entry point
 *
 * Return: If an error occurs, return EXIT_FAILURE.
 * Otherwise, if no commands have been executed, return EXIT_SUCCESS.
 * Otherwise, return the exit status of the most recently executed command.
 */
int main(void)
{
	state_t state = {
		EXIT_SUCCESS,
		0,
		NULL,
		NULL,
		0
	};
	ssize_t nread = 0;

	while (1)
	{
		printf("%s", PROMPT);
		nread = getline(&state.line, &state.linesz, stdin);
		if (nread < 0)
			state.status = EXIT_FAILURE;
		if (nread < 1)
			break;
		tokenize(&state);
		if (state.argv && state.argc > 0)
			state.status = dispatch(&state);
		free(state.argv);
		state.argc = 0;
		state.argv = NULL;
	}
	free(state.line);
	free(state.argv);
	return (state.status);
}
