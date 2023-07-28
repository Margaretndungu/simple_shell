#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_ARGS 64
#define READLINE_BUFFER_SIZE 1024
#define BUFFER_SIZE 1024
#define MAX_TOKENS 100

extern char **environ;
char *current_directory;

int prompt_user_file1(void);
char *read_line_file1(void);
void execute_command_file1(char *command);
void split_arguments_file2(char *line, char **args);
void execute_command_file2(char *line);
void tokenizeInput_file3(char *line, char **args);
char *findCommand_file3(char **args);
void executecommand_file3(char *command_path, char **args);
char *readCommand_file4(void);
char *searchCommandPath_file4(char *command);
void executeCommandChild(char *command);
void executeCommand_file4(char *command);
char *findCommandPath_file5(char *command, char *path);
void executeCommand_file5(char *line);
void printEnvironment_file5(void);
void executeCommand(char *line);
char *findExecutablePath(char *command __attribute__((unused)));
void printCommandNotFoundError(char *command);
int main(void);
char *read_input_line(void);
ssize_t read_input_chunk(char *buffer, size_t size);
char *process_input_data(const char *buffer, ssize_t chars_read, char *line, size_t *line_size);
int split_tokens(char *command, char *tokens[]);
char *extract_directory_argument(char *command);
void update_pwd_environment_variable(const char *new_dir, const char *previous_dir);
void change_directory(char *command);
#endif
