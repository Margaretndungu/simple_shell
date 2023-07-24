#include "main.h"
/**
 * readCommand_file4 - function that reads user input
 * Return:number of characters read, including the delimiter character
 */
char *readCommand_file4(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t read;

	read = getline(&line, &bufsize, stdin);

	if (read == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(line);
		return (NULL);
	}

	line[strcspn(line, "\n")] = '\0';

	return (line);
}
/**
 * searchCommandPath_file4 - function that allows you to retrieve
 * the value of an environment variable
 * @command: pointer to the command character
 * Return: string containing environment variable value
 */
char *searchCommandPath_file4(char *command)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		char command_with_path[MAX_ARGS];

		snprintf(command_with_path, sizeof(command_with_path),
			"%s/%s", token, command);

		if (access(command_with_path, X_OK) == 0)
		{
		return (strdup(command_with_path));
		}
		token = strtok(NULL, ":");
		}
		return (NULL);
}
/**
 * executeCommand_file4 - function that executes a command
 * @command:pointer to command character
 * Return: Nothing
 * and -1 on failure
 */
void executeCommand_file4(char *command)
{
pid_t pid = fork();
char *command_path;
char *args[MAX_ARGS];
int i = 0;

if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
	char *token = strtok(command, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	command_path = searchCommandPath_file4(args[0]);

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
	else
	{
	int status;

	waitpid(pid, &status, 0);
	}
	}
