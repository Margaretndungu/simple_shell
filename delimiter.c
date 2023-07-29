#include "main.h"
/**
 * handle_commands - function that handles command characters
 * @input:command to be handles
 * Return:Nothing
 */
void handle_commands(char *line, const char *delimiter)
{
	char *command = line;
	char *command_end;
	char *end;
	int prompt_result;
	char *input_command;

	while (command != NULL)
	{
		end = strchr(command, *delimiter);
		if (end != NULL)
		{
		*end = '\0';
		end++;
	}
		while (*command == ' ') command++;
		command_end = command + strlen(command) -1;
		while (*command_end == ' ')
		command_end--;
		*(command_end + 1) = '\0';

		prompt_result = prompt_user_file1();
		if (prompt_result == 0)
		{
			execute_command_file1(command);
			free(command);
		}
		else
		{
			input_command = read_line_file1();
			if (input_command == NULL)
			{
				break;
			}
			execute_command_file1(input_command);
			free(input_command);
		}
		command = end;
	}
}
