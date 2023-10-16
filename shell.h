#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ; /*An external variable for the "environment"*/
			/* Points to an array of pointers to strings*/

#define BUFFERSIZE 1024
#define TOKEN_BUFFSIZE 128
#define TOKEN_DELIM " \t\r\n\a"

/**
 * struct mydata - struct containing all necessary data for the shell
 * @argv: arg vector
 * @cmd_input: inputs by user on command line from keyboard
 * @args: The tokens of the command line
 * @stat: shell's last status
 * @count: count for lines
 * @env: environment variable
 * @pid: this shell's process ID
 */

typedef struct mydata
{
	char **argv;
	char *cmd_input;
	char **args;
	int stat;
	int count;
	char **env;
	char *pid;
} myshell;

/**
 * struct sep_s - singly linked list to store separators
 * @sep: separators (; | &)
 * @next: next node
 */

typedef struct sep_s
{
	char sep;
	struct sep_s *next;
} sep_t;

/**
 * struct line_s - singly linked list for lines
 * @line: the cmd line
 * @next: the next node
 */

typedef struct line_s
{
	char *line;
	struct line_s *next;
} line_t;

/**
 * struct varlist - singly linked list for var storage
 * @value_len: value length
 * @value: variable's value
 * @var_len: variable length
 * @next: next node
 */

typedef struct varlist
{
	int value_len;
	char *value;
	int var_len;
	struct varlist *next;
} varl;

/**
 * struct builtin - Builtin struct for cmd args.
 * @string: The name of cmd builtin
 * @d: datatype func pointer
 */
typedef struct builtin
{
	char *string;
	int (*d)(myshell *data);
} shell_builtin;


/*****functions str*************/
unsigned int _strspn(char *str, char *accept);
char *_strchr(char *str, char c);
int _strcmp(char *str1, char *str2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
int _isdigit(const char *str);
int char_check(char s[], const char *c);
char *_strtok(char string[], const char *delimiter);
int _strlen(const char *string);
char *_strdup(const char *string);
void rev_string(char *string);
int fetch_length(int num);
char *_itoa(int numb);
int _atoi1(char *str);
int _atoi(char *s);

/********errors******************/
char *catcd(myshell *data, char *mssg, char *err, char *str);
char *cd_error(myshell *data);
char *cmd_not_found(myshell *data);
char *exit_error(myshell *data);
char *env_error(myshell *data);
char *path_error(myshell *data);
int syntax_err(myshell *data, char *input);

/********lists*******************/
sep_t *add_node_sep(sep_t **h, char sept);
void free_separator(sep_t **h);
line_t *add_node_line(line_t **h, char *lane);
void free_line(line_t **h);
varl *add_node1(varl **h, int lenvar, char *val, int lenval);
void free_varl(varl **h);

/********mem*******************/
void _memcpy(void *dest, const void *src, unsigned int num);
void *_realloc(void *prev_str, unsigned int prev_size, unsigned int size);
char **_reallocdp(char **str, unsigned int prev_size, unsigned int size);

/*******cd func*********************/
void cdir_point(myshell *data);
void cd_next(myshell *data);
void cd_prev(myshell *data);
void cd_homerun(myshell *data);
int cd(myshell *data);

/**************exec***************/
int cd_col(char *path, int *index);
char *cmd_lock(char *commd, char **env);
int executable(myshell *data);
int cmd_errors(char *direc, myshell *data);
int cmnd_execute(myshell *data);
int execute(myshell *data);

/************env func*************/
int envir_cmp(const char *env_n, const char *str);
char *_getenv(const char *str, char **environ);
int _printenv(myshell *data);
int cmp_setenv(myshell *data);
char *cpy_data(char *str, char *val);
void _setenv(char *str, char *val, myshell *data);
int _unsetenv(myshell *data);

/************exit func*******/
int go_exit(myshell *data);

/***********builtin func******/
int (*fetch_builtin(char *cmnd))(myshell *);
int fetch_error(myshell *data, int err_value);
int help_msg(myshell *data);
void liner(char **line_p, size_t *s_line, char *buff, size_t s_buff);
ssize_t _getline(char **line_p, size_t *s_line, FILE *stream);
void signalc(int signal);

/*************help**************/
void help_env(void);
void help_set(void);
void help_unset(void);
void help_main(void);
void help_exit(void);
void get_help(void);
void help_alias(void);
void help_cd(void);

/************main*************/
void free_mydata(myshell *data);
void set_myshell_data(myshell *data, char **argv);
int main(int argc, char **argv);
char *_readline(int *ret_i_eof);
void envir_checker(varl **head, char *str, myshell *data);
int var_checker(varl **head, char *str, char *stat, myshell *mydata);
char *input_replace(varl **head, char *in, char *new_in, int length);
char *var_replace(char *in, myshell *data);
char *comment_del(char *str);
void myshell_loop(myshell *data);

/**********split func***************/
char **linesplitter(char *in);
int splitter(myshell *data, char *in);
void next_cmd(sep_t **separator, line_t **line, myshell *data);
void node_adder(sep_t **head_sep, line_t **head_line, char *in);
char *swapper(char *in, int bool);

#endif
