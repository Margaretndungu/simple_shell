#include "main.h"
/**
 * setenv_builtin - function that sets builtin
 * @variable:pointer to variable character
 * @value:pointer to the value to be set
 * Return:result
 */
int setenv_builtin(char *variable, char *value)
{
	int result = setenv(variable, value, 1);
	char *command;

	if (result != 0)
	{
		fprintf(stderr, "Error setting environment variable.\n");
	}
	else
	{
		prompt_user_file1();
		command = read_line_file1();
		if (command)
		{
			execute_command_file1(command);
			free(command);
		}
	}
	return (result);
}
/**
 * unsetenv_builtin - function that unsets builtin
 * @variable:pointer to variable character
 * Return:result
 */
int unsetenv_builtin(char *variable)
{
	int result = unsetenv(variable);
	char *command;

	if (result != 0)
	{
		fprintf(stderr, "Error unsetting environment variable.\n");
	}
	else
	{
	prompt_user_file1();
	command = read_line_file1();
	if (command)
	{
		execute_command_file1(command);
		free(command);
	}
	}
	return (result);
}
