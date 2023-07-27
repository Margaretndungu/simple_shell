#include "main.h"
/**
 * findCommandPath_file5 - function that finds a command in the path
 * @command:pointer to command character
 * @path:pointer to path character
 * Return:pointer to the next token
 */
char *findCommandPath_file5(char *command, char *path)
{
	char *token = custom_strtok(path, ":");

	while (token != NULL)
	{
		char command_path[MAX_ARGS];

		if (command[0] == '/')
		{
			snprintf(command_path, sizeof(command_path), "%s", command);
		}
		else
		{
			snprintf(command_path, sizeof(command_path), "%s/%s", token, command);
		}
		if (access(command_path, X_OK) == 0)
		{
		return (strdup(command_path));
		}
		token = custom_strtok(NULL, ":");
	}
	return (NULL);
}
/**
 * executeCommand_file5 - function that executes the line
 * @line: pointer to the line character
 * Return: Nothing
 */
void executeCommand_file5(char *line)
{
	char *args[MAX_ARGS];
	int i = 0;
	char *path;
	char *command_path;
	char *token = custom_strtok(line, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = custom_strtok(NULL, " ");
	}
	args[i] = NULL;

	path = getenv("PATH");

	command_path = findCommandPath_file5(args[0], path);

	if (command_path != NULL)
	{
		if (fork() == 0)
		{
			execve(command_path, args, NULL);
			perror("execve");
			free(command_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			int status;

			wait(&status);
		}
	}
	else
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
				}
				}
/**
 * printEnvironment_file5 - fuction that prints the environment variable
 * Return: string containg environment variable value
 */
void printEnvironment_file5(void)
{
int i;

for (i = 0; environ[i] != NULL; i++)
{
printf("%s\n", environ[i]);
}
}
