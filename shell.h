#ifndef _SHELL_H
#define _SHELL_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stddef.h>
#include <limits.h>
#include <sys/cdefs.h>

extern char **environ;
#define _TRUE            1
#define _FALSE           0

#define STDIN            0
#define STDOUT           1
#define STDERR           2

#define NON_INTERACTIVE  0
#define INTERACTIVE      1

#define PERMISSIONS      1
#define NON_PERMISSIONS -1

#define _FILE            10
#define NON_FILE         -10

#define _ENOENT          "No such file or directory"
#define _EACCES          "Permission denied"
#define _CMD_NOT_EXISTS  "not found"
#define _ILLEGAL_NUMBER  "Illegal number"

#define _CODE_ENOENT           3
#define _CODE_EACCES           13
#define _CODE_CMD_NOT_EXISTS   132
#define _CODE_ILLEGAL_NUMBER   133

/*struct function*/
typedef struct __attribute__((__packed__))
{
	int argc;                 /* For Number of arguments received */
	char **argv;              /* For Arguments received */
	int mode;                 /* INTERACTIVE or NON_INTERACTIVE */
	int error_code;           /* For error message */
	char *command;            /* Command to execute */
	int n_commands;           /* Number of commands executed */
	char *value_path;         /* Path of a command */
	int is_current_path;      /* Check if it is the current path or not */
	int status_code;          /* For Last exit code */
	char *buffer;             /* Line readed with the getline */
	char **arguments;         /* Line splited into words */
	char *environment;        /* Last environment variable get it */
	int pid;                  /* Process id */
} general_t;

typedef struct __attribute__((__packed__))
{
	char *message;            /* For Error message */
	int code;                 /* Error code for identify the error message */
} error_t;

typedef struct __attribute__((__packed__))
{
	char *command;
	void (*func)(general_t *info, char **arguments);
} builtin_t;

/*shell functions*/
void is_current_path(char *path, general_t *info);
void get_full_env(void);
void bin_env(general_t *info, char **command);
int builtins(general_t *info, char **arguments);
char **split_words(char *line, const char *sep);
void analyze(char **argus, general_t *info, char *yes);
int check_builtin(general_t *info, char **argus);
char *join_words(char *word1, char *word2, char *word3,  const char *sep);
char *_getenv(const char *name);
char *which(char *filename, general_t *info);
void prompt(general_t *info);
void sigintHandler(int sig_num);
void error(general_t *info);
void error_extra(general_t *info, char *extra);
char *read_prompt();
int current_directory(char *cmd, char **argus, char *buff, general_t *info);
void execute(char *command, char **arguments, general_t *info, char *buff);
char *message_selector(general_t info);
char *replacement(general_t *info, int *index, char *string);
char *replace_env(general_t *info, char *environment);
char *replace_value(general_t *info, int *index, char *string);
void bin_exit(general_t *info, char **arguments);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
void free_memory_p(void *ptr);
void free_memory_pp(void **ptr);
int number_controller(general_t *info, char *number);
int main(int argc, char **argv);
void analyze_patterns(general_t *info, char **arguments);
char *pattern_handler(general_t *info, char *string);
int print(char *msg);
int _putchar(char c);
void start(general_t *info);
void start_prompt(general_t *info);
int print_err(char *msg);
int _putchar_to_fd(char c, int fd);
int print_to_fd(char *msg, int fd);
int is_file(char *file);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(char *msg);
int is_executable(char *filename);
int _atoi(char *s);
int contains_letter(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
int is_numerical(unsigned int n);
char *to_string(int number);
int digits(int n);
#endif
