#include "main.h"

/**
  * tokenizeInput_file3 - tokenize a line
  * @line: pointer to be tokenized
  * @args: pointer to argument character
  *
  * Return: pointer to next token or
  * NULL if there are no more tokens
  */

void tokenizeInput_file3(char *line, char **args)
{
	int i = 0;
	char *token;

	token = strtok(line, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

/**
  * findCommand_file3 - finds command in a file
  * @args: pointer to next argument
  *
  * Return: string containing environment variable value
  */

char *findCommand_file3(char **args)
{
	char *path = getenv("PATH");
	char *command_path = NULL;
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		char command[MAX_ARGS];

		if (args[0][0] == '/')
		{
			snprintf(command, sizeof(command), "%s", args[0]);
		}
		else
		{

			snprintf(command, sizeof(command), "%s/%s", token, args[0]);
		}

		if (access(command, X_OK) == 0)
		{
			free(command_path);

			command_path = strdup(command);
			break;
		}
		token = strtok(NULL, ":");
	}
	return (command_path);
}

/**
  * executecommand_file3 - executes a command path
  * @command_path: pointer to command_path character
  * @args: pointer to character argument
  *
  * Return: Nothing or -1 on error
  */

void executecommand_file3(char *command_path, char **args)
{
	if (command_path != NULL)
	{
		execve(command_path, args, NULL);
		perror("execve");
		free(command_path);
	}
	else
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
	}
	exit(EXIT_FAILURE);
}
