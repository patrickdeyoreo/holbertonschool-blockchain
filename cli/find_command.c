#include <string.h>

#include "cli.h"

/**
 * find_command - find a command by name
 *
 * @name: name of the command to find
 *
 * Return: If no such command exists, return NULL.
 * Otherwise, return a pointer to the found command.
 */
command_t const *find_command(char const *name)
{
	command_t const *command = get_commands();

	while (command->name)
	{
		if (strcmp(name, command->name) == 0)
			return (command);
		command += 1;
	}
	return (NULL);
}

