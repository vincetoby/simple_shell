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
#include <stdbool.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARG_COUNT 100
#define X_OK 1 /*1 represents executable permission*/
extern char **environ;


/***************parser************/
void parser(char *std_input, char **argv, int *argc);

/****************PATH_handler*************/
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
int _strncmp(const char *str1, const char *str2, size_t num);
char *_strchr(const char *str, int c);
int _strcmp1(const char *s1, char *s2);

/*******************functions3*******************/
char *_getenv(const char *var);
int _atoi(char *str);
size_t _strspn(const char *str, const char *set);
size_t _strcspn(const char *str, const char *set);
char *_strtok(char *str, const char *delim);
char *get_cd_path();

/********************function4******************/
size_t _token_counter(const char *str, char *delim);


/**************executor*************/
int execute_cmd(const char *cmd, char *const argv[]);
void execute_cmd2(char *command);

/**********errors********************/
void command_not_found(const char *command);
void err_pathenv(void);
void err_setenv(void);
void err_unsetenv(void);

/***********built-in1*****************/
void handle_exit(char *buffer);
void handle_env();
void handle_clear();

/******************built-in2**************/
void handle_set_unset(char *buffer);
void handle_setenv(char *var, char *str);
void handle_unsetenv(char *env);

/*************getline*******************/
#define BUFF_SIZE 1024
char *_getline();
char *resize_line(char *line, size_t new_size);

/****************handler*****************/
void handle_builtin(char *buffer);
void handle_builtin2(char *buffer);
void change_dir(const char *dir);

#endif
