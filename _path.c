#include "main.h"
/**
 * getCurrentWorkingDirectory - retrieves the current working directory
 *
 * Return: dynamically allocated copy
 */
char *getCurrentWorkingDirectory(void)
{
	char *cwd = malloc(1024);

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

/**
 * restoreWorkingDirectory - restores current working directory
 * @saved_directory: string
 *
 * Return: Nothing
 */
void restoreWorkingDirectory(char *saved_directory)
{
	if (chdir(saved_directory) == -1)
	{
		perror("chdir");
	}
	free(saved_directory);
}
