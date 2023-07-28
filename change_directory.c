#include "main.h"
/**
 * change_directory - function that changes directory
 * @command: pointer to cd character
 * Return: Nothing
 */
void change_directory(char *command)
{
	char *arg = extract_directory_argument(command);
	char *previous_directory = getcwd(NULL, 0);
	char *line;

	if (arg == NULL)
	{
		fprintf(stderr, "Error: Invalid command format.\n");
		return;
	}

	if (chdir(arg) != 0)
	{
		perror("chdir");
		free(previous_directory);
		return;
	}
	update_pwd_environment_variable(arg, previous_directory);
	free(previous_directory);

	prompt_user_file1();
	line = read_line_file1();

	execute_command_file1(line);
	free(line);
}
/**
 * extract_directory_argument - function that extracts directory arguments
 * from a cd
 * @command: cd command and optional directory argument
 * Return: The extracted directory argument or NULL on failure
 */
char *extract_directory_argument(char *command)
{
	char *arg = strchr(command, ' ');

	if (arg != NULL)
	{
		arg++;
		arg[strcspn(arg, "\n")] = '\0';
	}
	else
	{
		arg = getenv("HOME");
	if (arg == NULL)
	{
		fprintf(stderr, "Error: $HOME environment variable not set.\n");
		return (NULL);
	}
	}
	return (arg);
}
/**
 * update_pwd_environment_variable - function that updates  the PWD
 * environment variable
 * @new_dir: the new directory path
 * @previous_dir: pointer to previous directory path
 * Return: Nothing
 */
void update_pwd_environment_variable(const char *new_dir, const
		char *previous_dir)
{
	if (setenv("PWD", new_dir, 1) != 0)
	{
		perror("setenv");
		chdir(previous_dir);
	}
	else
	{
		free(current_directory);
		current_directory = getcwd(NULL, 0);
	}
}
/**
 * handle_cd - function that handles the cd command
 * @command: pointer to command character
 * Return:Nothing
 */
void handle_cd(char *command)
{
	char *arg = extract_directory_argument(command);

	if (arg == NULL)
	{
		fprintf(stderr, "Error: Invalid command format.\n");
		return;
	}

	if (chdir(arg) != 0)
	{
		perror("chdir");
	}
}
/**
 * handle_pwd - function that handles the pwd command
 * Return: Nothing
 */
void handle_pwd(void)
{
	char *current_dir = getcwd(NULL, 0);
	printf("%s\n", current_dir);
	free(current_dir);
}
