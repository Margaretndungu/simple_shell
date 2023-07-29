#include "main.h"
/**
 * handle_commands - function that handles command characters
 * @input:command to be handles
 * Return:Nothing
 */
void handle_commands(char *line, const char *delimiter)
{
	char *command = strtok(line, delimiter);

	while (command != NULL)
	{
		command = strtok(NULL, delimiter);
	}
}
