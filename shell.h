#ifndef shell_H
#define shell_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct datas
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datast);
} builtin_t;

/* cham_lists.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* cham_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* cham_str.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *str, char c);
int _strspn(char *str, char *accept);

/* cham_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **dp, unsigned int old_size, unsigned int new_size);

/* cham_str2.c */
char *_strdup(const char *s);
size_t _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* cham_str3.c */
void revs_string(char *str);

/* check_parse_error.c*/
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_parse_error(data_shell *datast, char *input, int i, int);
int check_parse_error(data_shell *datast, char *input);

/* shell_lp.c */
char *no_comment(char *in);
void shell_lp(data_shell *datast);

/* read_shell_line.c */
char *read_line(int *i_eof);

/* split1.c */
char *swap_char(char *input, int);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void gTo_next(sep_list **list_s, line_list **list_l, data_shell *datast);
int split1_commands(data_shell *datast, char *input);
char **split_line(char *input);

/* rep_vars.c */
void check_env(r_var **h, char *in, data_shell *datas);
int check_var(r_var **h, char *in, char *st, data_shell *datas);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_vars(char *input, data_shell *datast);

/* get_line.c */
void built_line(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(data_shell *datast);

/* cmd_exec.c */
int colon_cdir(char *path, int *i);
char *_locate(char *cmd, char **_environ);
int is_executable(data_shell *datast);
int check_error_cmd(char *dir, data_shell *datast);
int cmd_exec(data_shell *datast);

/* shell_env1.c */
int cmp_env_name(const char *envn, const char *name);
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datast);

/* shell_env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datast);
int _setenv(data_shell *datast);
int _unsetenv(data_shell *datast);

/* cd_do.c */
void cd_do(data_shell *datast);
void cd_to(data_shell *datast);
void cd_previous(data_shell *datast);
void cd_to_home(data_shell *datast);

/*  cd_dr.c */
int cd_dr(data_shell *datast);

/* get_builtin */
/* int (*get_builtin(char *cmd))(data_shell *datast); */

/* shell_exit.c */
int shell_exit(data_shell *datast);

/* cham_stdlib.c */
int getN_len(int n);
char *my_itoa(int n);
int my_atoi(char *s);

/* cham_error1.c */
char *strcat_cd(data_shell *datast, char *msg, char *errno_msg, char *ver_str);
char *error_get_cd(data_shell *datast);
char *error_not_found(data_shell *datast);
char *error_exit_shell(data_shell *datast);

/* cham_error2.c */
char *error_get_alias(char **args);
char *error_env(data_shell *datast);
char *error_parse(char **args);
char *error_permission(char **args);
char *error_path(data_shell *datast);


/* get_error.c */
int get_error(data_shell *datast, int eval);

/* sigint_handler.c */
void sigint_handler(int sig);

/*cham_help.c */
void cham_help_env(void);
void cham_help_setenv(void);
void cham_help_unsetenv(void);
void cham_help_general(void);
void cham_help_exit(void);

/* cham_help2.c */
void cham_help(void);
void cham_help_alias(void);
void cham_help_cd(void);

/* get_help.c */
int get_help(data_shell *datast);

/* shell.c */
void int_data(data_shell *datast, char **av);
void free_data(data_shell *datast);
int main(int ac, char **av);

#endif /* shell_H */
