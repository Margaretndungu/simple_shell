#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

extern char **environ;

void prompt_user_file(void);
char *read_line_file1(void);
void execute_command_file1(char *command);
void split_arguments_file2(char *line, char **args);
void execute_command_file2(char *line);
void tokenizeInput_file3(char *line, char **args);
char *findCommand_file3(char **args);
void executeCommand_file3(char *command_path, char **args);
char *readCommand_file4(void);
char *searchCommandPath_file4(char *command);
void executeCommand_file4(char *command);
char *findCommandPath_file5(char *command, char *path);
void executeCommand_file5(char *line);
void printEnvironment_file5(void);
int executeCommmand(char *line);

#endif
