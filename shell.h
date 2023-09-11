#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 100
#define X_OK 1 /*1 represents executable permission*/


/***************parser************/
void parser(char *std_input, char **argv, int *argc);

/****************PATH*************/
char *path_search(const char *command);

/***************function1**********/
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
int _strlen(char *s);
int _strlen1(const char *s);
char *_strdup(char *str);

/****************function2***********/
int _strcmp(char *s1, char *s2);
char *_strcpy1(char *dest, const char *src);

/**************executor*************/
int execute_cmd(const char *cmd, char *const argv[]);

/**********errors********************/
void command_not_found(const char *command);

/***********built-in1*****************/
void handle_exit();
void handle_env();

#endif
