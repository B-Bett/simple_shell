#include <stdio.h>
/**
 * main - start of command line
 * @argc: no of arguemnts
 * @argv: vector of characters
 * Return: 0
 */
int main(int argc, char *argv[])
{
	printf("allan is my partner\n");
	printf("simple shell project 0.1+>\n");
	fflush(stdout);
	printf("argc = %\n", argc);
	int i;

	for (int i = 0; i < 6; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
	return (0);
}
