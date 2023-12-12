#include "shell.h"

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @datast: data relevant (directory)
 * @msg: contenated message to print
 * @errno_msg: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd(data_shell *datast, char *msg, char *errno_msg, char *ver_str)
{
	char *illegal_flag;

	_strcpy(errno_msg, datast->av[0]);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, ver_str);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, datast->args[0]);
	_strcat(errno_msg, msg);
	if (datast->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datast->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(errno_msg, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(errno_msg, datast->args[1]);
	}

	_strcat(errno_msg, "\n");
	_strcat(errno_msg, "\0");
	return (errno_msg);
}

/**
 * error_get_cd - error message for cd command in get_cd
 * @datast: data relevant (directory)
 * Return: Error message
 */
char *error_get_cd(data_shell *datast)
{
	int length, len_id;
	char *errno_msg, *ver_str, *msg;

	ver_str = my_itoa(datast->counter);
	if (datast->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datast->args[1]);
	}

	length = _strlen(datast->av[0]) + _strlen(datast->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	errno_msg = malloc(sizeof(char) * (length + 1));

	if (errno_msg == 0)
	{
		free(ver_str);
		return (NULL);
	}

	errno_msg = strcat_cd(datast, msg, errno_msg, ver_str);

	free(ver_str);
	return (errno_msg);
}

/**
 * error_not_found - generic error message for command not found
 * @datast: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(data_shell *datast)
{
	int length;
	char *errno_msg;
	char *ver_str;

	ver_str = my_itoa(datast->counter);
	length = _strlen(datast->av[0]) + _strlen(ver_str);
	length += _strlen(datast->args[0]) + 16;
	errno_msg = malloc(sizeof(char) * (length + 1));
	if (errno_msg == 0)
	{
		free(errno_msg);
		free(ver_str);
		return (NULL);
	}
	_strcpy(errno_msg, datast->av[0]);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, ver_str);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, datast->args[0]);
	_strcat(errno_msg, ": not found\n");
	_strcat(errno_msg, "\0");
	free(ver_str);
	return (errno_msg);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @datast: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(data_shell *datast)
{
	int length;
	char *errno_msg;
	char *ver_str;

	ver_str = my_itoa(datast->counter);
	length = _strlen(datast->av[0]) + _strlen(ver_str);
	length += _strlen(datast->args[0]) + _strlen(datast->args[1]) + 23;
	errno_msg = malloc(sizeof(char) * (length + 1));
	if (errno_msg == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(errno_msg, datast->av[0]);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, ver_str);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, datast->args[0]);
	_strcat(errno_msg, ": Illegal number: ");
	_strcat(errno_msg, datast->args[1]);
	_strcat(errno_msg, "\n\0");
	free(ver_str);

	return (errno_msg);
}
