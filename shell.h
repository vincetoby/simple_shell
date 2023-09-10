#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_BUFFER_SIZE 100


/***************parser************/
void parser(char *std_input, char **argv, int *argc);

#endif
