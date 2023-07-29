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

			line = read_line_file1();

			if (line == NULL)
			{
				break;
			}
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		else if (strncmp(line, "cd", 2) == 0)
		{
			handle_cd(line);
		}
		else if (strcmp(line, "pwd") == 0)
		{
			handle_pwd();
		}
		else if (strncmp(line, "setenv", 6) == 0)
	{
		char *variable = strtok(line + 6, " ");
		char *value = strtok(NULL, " ");

		if (variable && value)
		{
			setenv_builtin(variable, value);
		}
		else
		{
			fprintf(stderr, "Invalid setenv command\n");
		}
		}
		else if (strncmp(line, "unsetenv", 8) == 0)
		{
		char *variable = strtok(line + 8, " ");
		if (variable)
		{
			unsetenv_builtin(variable);
		}
		else
		{
			fprintf(stderr, "Invalid unsetenv command\n");
		}
	}
	else if (strcmp(line, "env") == 0)
	{
		handle_env();
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
 * handle_env - function that handles env
 * Return:Nothing
 */
void handle_env(void)
{
			int i = 0;
			while (environ[i] != NULL)
			{
				printf("%s\n", environ[i]);
				i++;
			}
			printEnvironment_file5();
}
/**
 * executeCommand - function that calls executable files
 * @line:line to be executed
 * Return: 0 on success and -1 on failure
 */
void executeCommand(char *line)
{
	char *command_path;
	int status;
	pid_t pid;
	char *args[MAX_ARGS];
	int i;

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			return;
		}
		else if (pid == 0)
		{
			tokenizeInput_file3(line, args);
			command_path = findCommand_file3(args);

			if (command_path != NULL)
			{
				execve(command_path, args, NULL);
				perror("execve");
			}
			else
			{
				printCommandNotFoundError(args[0]);
			}
			free(command_path);

			for (i = 0; args[i] != NULL; i++)
			{
				free(args[i]);
			}
			free(line);
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
