#include "main.h"
/**
 * main - entry point
 * @argc: argument count
 * @argv[]:argument vector
 * Return: Always 0 (success)
 */
int main1(int argc, char *argv[])
{
	FILE *file;
	char *command = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
                exit(EXIT_FAILURE);
	}
		file = fopen(argv[1], "r");
		if (!file)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		else
		{
			execute_command_file1(command);
			free(command);
		}
		fclose(file);
	return (0);
}
