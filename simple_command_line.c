#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * read_input - Read user input from stdin
 *
 * This function reads a line of input from the standard input (stdin) and
 * returns it as a null-terminated string.
 *
 * Return: A pointer to the user's input string or NULL on EOF (Ctrl+D).
 */

char *read_input()
{
	static char input[MAX_INPUT_SIZE];

	printf("($) ");
	fflush(stdout);
	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		if (feof(stdin))
		{
			printf("\nExiting the shell.\n");
			return (NULL);
		}
		else
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
	}
	input[strcspn(input, "\n")] = '\0';
	return (input);
}

/**
 * execute_command - Execute a command in a child process
 *
 * This function takes a command as input, forks a child process, and executes
 * the command in the child process. It also waits for the child process to
 * complete and handles any errors or signals.
 *
 * @param command: The command to execute.
 */

void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("./hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[] = {command, NULL};

		if (execve(command, args, NULL) == -1)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);

			if (exit_status != 0)
			{
				printf("Command failed with exit status %d\n", exit_status);
			}
		}
		else if (WIFSIGNALED(status))
		{
			printf("Command terminated by signal %d\n", WTERMSIG(status));
		}
	}
}

/**
 * main - Simple UNIX command line interpreter (shell)
 *
 * This is the main function of the simple shell. It continuously reads user
 * input, executes commands, and handles errors and signals.
 *
 * Return: Always 0
 */

int main(void)
{
	char *input;

	while (1)
	{
		input = read_input();
		if (input == NULL)
		{
			break;
		}

		execute_command(input);
	}

	return (0);
}
