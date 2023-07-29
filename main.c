#include "main.h"
/**
 * main - entry point
 * Return:Always 0 (success)
 */
int main(void)
{
	char *line;

	while (1)
	{
		prompt_user_file1();
		fflush(stdout);

		line = my_getline();

		if (line == NULL)
		{
			break;
		}
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		if (strcmp(line, "env") == 0)
		{
			printEnvironment_file5();
		}
		else
		{
		executeCommand(line);
		}

		free(line);
	}
	return (0);
}
/**
 * handleCommand - function to execute multiple commands
 * @line: line to be executed
 *
 * Return: Nothing
 */
void handleCommand(char *line)
{
	char *command;
	char *saved_directory;
	char *line_copy = strdup(line);

	command = strtok(line_copy, ";");

	while (command != NULL)
	{
		saved_directory = getCurrentWorkingDirectory();

		executeCommand(command);

		restoreWorkingDirectory(saved_directory);

		command = strtok(NULL, ";");
	}
	free(line_copy);
}
/**
 * executeCommand - function that calls executable files
 * @line:line to be executed
 * Return: 0 on success and -1 on failure
 */
void executeCommand(char *command)
{
	char *command_path;
	int status;
	pid_t pid;
	char *args[MAX_ARGS];

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		tokenizeInput_file3(command, args);
		command_path = findCommand_file3(args);

		if (command_path != NULL)
		{
			execve(command_path, args, NULL);
			perror("execve");
			free(command_path);
		}
		else
		{
			printCommandNotFoundError(args[0]);
		}
		free(command);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * findExecutablePath - function that find executable path
 * @command: command to be found
 * Return: Nothing
 */
char *findExecutablePath(char *command __attribute__((unused)))
{
	return (NULL);
}
/**
 * printCommandNotFoundError - function prints an error message
 * @command:command to be executed
 * Return:Nothing
 */
void printCommandNotFoundError(char *command)
{
	char error_message[] = "Command not found: ";

	write(STDERR_FILENO, error_message, strlen(error_message));
	write(STDERR_FILENO, command, strlen(command));
	write(STDERR_FILENO, "\n", 1);
}
