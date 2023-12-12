#include "shell.h"

/**
 * _memcpy - function that copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * my_realloc - resizes the memory block previously allocated.
 * @ptr: pointer to the memory block to be resized.
 * @old_size: size, in bytes, of the memory block.
 * @new_size: new size, in bytes,for the memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr to resized memory.
 * if malloc fails or if @new_size is 0, returns NULL.
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @dp: double pointer to the memory reallocated.
 * @old_size: size, in bytes, of the double pointer.
 * @new_size: new size, in bytes, of the double pointer.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr to resized memory.
 * if malloc fails or if @new_size is 0, returns NULL.
 */
char **_reallocdp(char **dp, unsigned int old_size, unsigned int new_size)
{
	char **new_dp;
	unsigned int i;

	if (dp == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (dp);

	new_dp = malloc(sizeof(char *) * new_size);
	if (new_dp == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		new_dp[i] = dp[i];

	free(dp);

	return (new_dp);
}
