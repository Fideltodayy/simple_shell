#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_type;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_type *env;
	list_type *history;
	list_type *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;	  /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_type;

#define INFO_INIT                                                               \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_type *);
} builtin_table;

/* shloop.c */
int hsh(info_type *, char **);
int find_builtin(info_type *);
void find_cmd(info_type *);
void fork_cmd(info_type *);

/* parser.c */
int is_cmd(info_type *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_type *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfree(void **);

/* atoi.c */
int interactive(info_type *);
int is_delimeter(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c */
int _erratoi(char *);
void print_error(info_type *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin.c */
int _myexit(info_type *);
int _mycd(info_type *);
int _myhelp(info_type *);

/* builtin1.c */
int _myhistory(info_type *);
int _myalias(info_type *);

/*getline.c */
ssize_t get_input(info_type *);
int _getline(info_type *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void clear_info(info_type *);
void set_info(info_type *, char **);
void free_info(info_type *, int);

/* environ.c */
char *_getenv(info_type *, const char *);
int _myenv(info_type *);
int _mysetenv(info_type *);
int _myunsetenv(info_type *);
int populate_env_list(info_type *);

/* getenv.c */
char **get_environ(info_type *);
int _unsetenv(info_type *, char *);
int _setenv(info_type *, char *, char *);

/* history.c */
char *get_history_file(info_type *info);
int write_history(info_type *info);
int read_history(info_type *info);
int build_history_list(info_type *info, char *buf, int linecount);
int renumber_history(info_type *info);

/* lists.c */
list_type *add_node(list_type **, const char *, int);
list_type *add_node_end(list_type **, const char *, int);
size_t print_list_str(const list_type *);
int delete_node_at_index(list_type **, unsigned int);
void free_list(list_type **);

/* lists1.c */
size_t list_len(const list_type *);
char **list_typeo_strings(list_type *);
size_t print_list(const list_type *);
list_type *node_starts_with(list_type *, char *, char);
ssize_t get_node_index(list_type *, list_type *);

/* vars.c */
int is_chain(info_type *, char *, size_t *);
void check_chain(info_type *, char *, size_t *, size_t, size_t);
int replace_alias(info_type *);
int replace_vars(info_type *);
int replace_string(char **, char *);

#endif
