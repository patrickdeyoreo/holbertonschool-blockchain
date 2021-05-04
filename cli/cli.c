#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cli.h"

/**
 * dispatch - dispatch a command by calling the associated function
 *
 * @state: 
 * Return: If an error occurs or the command does not exist, return -1.
 * Otherwise, return the exit status of the executed command.
 */
static int dispatch(state_t *state)
{
	static command_t commands[] = {
		{cli_exit, EXIT_NAME, EXIT_HELP, EXIT_DESC},
		{cli_help, HELP_NAME, HELP_HELP, HELP_DESC},
		{cli_info, INFO_NAME, INFO_HELP, INFO_DESC},
		{cli_load, LOAD_NAME, LOAD_HELP, LOAD_DESC},
		{cli_mine, MINE_NAME, MINE_HELP, MINE_DESC},
		{cli_save, SAVE_NAME, SAVE_HELP, SAVE_DESC},
		{cli_send, SEND_NAME, SEND_HELP, SEND_DESC},
		{cli_wallet_load, WALLET_LOAD_NAME, WALLET_LOAD_HELP, WALLET_LOAD_DESC},
		{cli_wallet_save, WALLET_SAVE_NAME, WALLET_SAVE_HELP, WALLET_SAVE_DESC},
		{NULL, NULL, NULL, NULL}
	};
	command_t *command = commands;

	while (command->name)
	{
		if (strcmp(state->argv[0], command->name) == 0)
			return (command->func(state));
		command += 1;
	}
	return (-1);
}

/**
 * tokenize - tokenize a line
 *
 * @line: pointer to the start of the line to tokenize
 * @nptr: address at which to store the number of tokens
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the first element of a NULL-terminated
 * array containing the tokenized line.
 */
static char **tokenize(char *line, int *nptr)
{
	char *linedup = strdup(line);
	char **tokens = NULL;
	char *token = NULL;
	int ntokens = 0;

	if (!linedup)
		return (NULL);

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
	token = strtok(line, BLANK);
	if (token)
	{
		do {
			tokens[ntokens] = token;
			ntokens += 1;
			token = strtok(NULL, BLANK);
		} while (token);
	}
	*nptr = ntokens;
	return (tokens);
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
		NULL
	};
	char *line = NULL;
	size_t linesz = 0;
	ssize_t nread = 0;

	while (1)
	{
		printf("%s", PROMPT);
		nread = getline(&line, &linesz, stdin);
		if (nread < 0)
			state.status = EXIT_FAILURE;
		if (nread < 1)
			break;
		state.argv = tokenize(line, &state.argc);
		if (state.argv && state.argc > 0)
			state.status = dispatch(&state);
		free(state.argv);
		state.argc = 0;
		state.argv = NULL;
	}
	free(line);
	free(state.argv);
	return (state.status);
}
