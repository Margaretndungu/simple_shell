#include "main.h"
/**
 * split_tokens - function that splits tokens a command
 * @command:pointer to a command character
 * @tokens: pointer to a token character array
 * Return:token count
 */
int split_tokens(char *command, char *tokens[])
{
	int i = 0;
	int len = strlen(command);
	int token_count = 0;
	int token_start = 0;
	int result;
	char *line;

	while (i <= len)
	{
		if (command[i] == ' ' || command[i] == '\t' || command[i] == '\0')
		{
			if (i > token_start)
			{
				tokens[token_count++] = &command[token_start];
			}
			command[i] = '\0';
			token_start = i + 1;
		}
		i++;
	}
	result = prompt_user_file1();
	printf("prompt_user_file1 returned: %d\n", result);

	line = read_line_file1();
	printf("read_line_file1 returned: %s\n", line);

	execute_command_file1(tokens[0]);

	return (token_count);
}

