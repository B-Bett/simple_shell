#include "shell.h"

/**
 * bfree - free a pointer and the NULLs in the address
 * @ptr: address of the pointer to freed
 *
 * Return: 1 if freed, otherwise 0.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}