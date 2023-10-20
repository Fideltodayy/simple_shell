#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


#define PROMPT "#cisfun$ "
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CNVRT_L_CASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


extern char **environ;

/**
 * struct liststr - Structure for a linked list of integer-string pairs
 * @num: An integer value
 * @str: A string value
 * @next: Pointer to the next element in the list
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_type;

/**
 *struct passinfo - Structure for holding information about
 *                  a command or program.
 *
 * @arg: The command argument
 * @argv: Array of command arguments
 * @path: The path to the command
 * @argc: Number of command arguments
 * @line_count: Line count (line number) in the script
 * @err_num: Error number
 * @linecount_flag: Flag indicating line count
 * @fname: File name
 * @env: Environment variable list
 * @history: Command history list
 * @alias: Alias list
 * @environ: Environment variables
 * @env_changed: Flag indicating if the environment has changed
 * @status: Command status
 * @cmd_buf: Pointer to command ; chain buffer, for memory management
 * @cmd_buf_type: Command buffer type (CMD_type: ||, &&, ;)
 * @readfd: File descriptor for reading
 * @histcount: History count
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
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_type;


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

/* atoi_functions.c */
int is_interactive(info_type *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* built_in_functions.c */
int _myexit(info_type *);
int _mycd(info_type *);
int _myhelp(info_type *);

/* dynamic_memory_functions */
int bfree(void **);

/* environ.c */
int _myenv(info_type *);
char *_getenv(info_type *, const char *);
int _mysetenv(info_type *);
int _myunsetenv(info_type *);
int populate_env_list(info_type *);

/* error_handling_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* get_env.c */
char **get_environ(info_type *);
int _unsetenv(info_type *, char *);
int _setenv(info_type *, char *, char *);

/* get_info.c */
void clear_info(info_type *);
void set_info(info_type *, char **);
void free_info(info_type *, int);


/* get_line_functions.c */
ssize_t input_buf(info_type *, char **, size_t *);
ssize_t get_input(info_type *);
ssize_t read_buf(info_type *, char *, size_t *);
int _getline(info_type *, char **, size_t *);
void handle_interrupt_signal(__attribute__((unused))int);

/* history.c */
char *construct_history_file_path(info_type *info);
int write_history(info_type *info);
int read_history(info_type *info);
int build_history_list(info_type *info, char *buf, int linecount);
int renumber_history(info_type *info);

/* lists_handling_functions.c*/
list_type *add_node(list_type **, const char *, int);
list_type *add_node_end(list_type **, const char *, int);
size_t print_environment_variables(const list_type *);
int delete_node_at_index(list_type **, unsigned int);
void free_list(list_type **);

/* more_built_in_functions.c */
int _myhistory(info_type *);
int unset_alias(info_type *, char *);
int set_alias(info_type *, char *);
int print_alias(list_type *);
int _myalias(info_type *);

/* more_dynamic_memory_functions.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* more_error_handling_functions.c */
int _erratoi(char *);
void print_error(info_type *, char *);
int print_integer(int, int);
char *convert_long_to_string(long int, int, int);
void remove_comments(char *);

/* more_lists_handling_functions.c */
size_t list_len(const list_type *);
char **list_typeo_strings(list_type *);
size_t print_list(const list_type *);
list_type *node_starts_with(list_type *, char *, char);
ssize_t get_node_index(list_type *, list_type *);

/* more_strings_functions.c */
int hsh(info_type *, char **);
int find_builtin(info_type *);
void find_cmd(info_type *);
void fork_cmd(info_type *);

/* parser_functions.c */
int is_command(info_type *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_type *, char *, char *);

/* strings_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* strings_more.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow_2(char *, char);

/* vars.c */
int is_chain(info_type *, char *, size_t *);
void check_chain(info_type *, char *, size_t *, size_t, size_t);
int replace_alias(info_type *);
int replace_vars(info_type *);
int replace_string(char **, char *);

#endif
