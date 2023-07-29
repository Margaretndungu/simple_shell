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

	if (path == NULL)
	{
		return(NULL);
	}

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
 * executeCommandChild - function that execute the child process
 * @command:pointer to command character
 * Return:pointer to the next token
 */
void executeCommandChild(char *command)
{
	char *args[MAX_ARGS];
	int i = 0;
	char *token = strtok(command, " ");
	char *command_path;

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
		exit(127);
	}
	else
	{
		const char *command_not_found_msg = "Command not found: ";

		write(STDERR_FILENO, command_not_found_msg, strlen(command_not_found_msg));
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, "\n", 1);
		free(command_path);
		exit(127);
	}
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
int status;
int exit_status;

if (strncmp(command, "exit ", 5) == 0 || (atoi(command) != 0 && command[0] != '0'))
{
	if (strncmp(command, "exit ", 5) == 0)
	{
	exit_status = atoi(command + 5);
	}
	else
	{
		exit_status = atoi(command);
	}

	printf("shell exit status: %d\n", exit_status);

	exit(exit_status);
}
if (pid == -1)
{
	perror("fork");
	exit(EXIT_FAILURE);
}
else if (pid == 0)
{
	executeCommandChild(command);
}
else
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status != 0 && exit_status != 127)
		{
			exit(exit_status);
		}
	}
}
}
