0x16. C - Simple Shell

A simple shell is a command-line interface that provide a basic way to interact with an operating system. it acts as a mediator between the user and the operating system, allowing  users to execute commands and manage various tasks. the shell typically provides features such as command parsing, process execution, and input/output redirection

users interact with the shell by typing commands, which are then interpreted and executed by the shell. it supports basic functionalities like navigating the file system, running programs and managing files and directories. the shell also offers features like command history, tab completion and customizable prompt setting to enhance the user experience.

in our shell we use getline to read user input and execve to execute the command. we also use strtok to tokenize line inputed by the user and fork tocreate a child process.
