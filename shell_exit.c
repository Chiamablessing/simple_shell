#include "shell.h"

/**
 * shell_exit - function that exits the shell
 *
 * @datast: data relevant (status and args)
 * Return: 0 on success.
 */
int shell_exit(data_shell *datast)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datast->args[1] != NULL)
	{
		ustatus = my_atoi(datast->args[1]);
		is_digit = _isdigit(datast->args[1]);
		str_len = _strlen(datast->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(datast, 2);
			datast->status = 2;
			return (1);
		}
		datast->status = (ustatus % 256);
	}
	return (0);
}
