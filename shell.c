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

/**
 * main: contains the main function
 * _myommand: the command to be exeuted
 * Return: always 0
 */
#define MAX_COMMAND_LENGTH 256

int main(void)
{
	char _mycommand[MAX_COMMAND_LENGTH];

	while (1)
	{
		printf("simple_shell> ");
		fflush(stdout);
		if (fgets(_mycommand, sizeof(_mycommand), stdin) == NULL)
		{
			printf("\nGoodbye!\n");
			break;
		}
		_mycommand[strcspn(_mycommand, "\n")] = '\0';
		pid_t pid = fork();

		if (pid == -1)

		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execlp(_mycommand, _mycommand, NULL) == -1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int status;

			waitpid(pid, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			{
				printf("Command failed with status %d\n", WEXITSTATUS(status));
			}
		}
	}
	return (0);
}
