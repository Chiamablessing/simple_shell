#include "shell.h"

/**
 * error_env - error message for env in get_env.
 * @datast: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(data_shell *datast)
{
	int length;
	char *errno_msg;
	char *ver_str;
	char *msg;

	ver_str = my_itoa(datast->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(datast->av[0]) + _strlen(ver_str);
	length += _strlen(datast->args[0]) + _strlen(msg) + 4;
	errno_msg = malloc(sizeof(char) * (length + 1));
	if (errno_msg == 0)
	{
		free(errno_msg);
		free(ver_str);
		return (NULL);
	}

	strcpy(errno_msg, datast->av[0]);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, ver_str);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, datast->args[0]);
	_strcat(errno_msg, msg);
	_strcat(errno_msg, "\0");
	free(ver_str);

	return (errno_msg);
}
/**
 * error_path- error message for path and failure denied permission.
 * @datast: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path(data_shell *datast)
{
	int length;
	char *ver_str;
	char *errno_msg;

	ver_str = my_itoa(datast->counter);
	length = _strlen(datast->av[0]) + _strlen(ver_str);
	length += _strlen(datast->args[0]) + 24;
	errno_msg = malloc(sizeof(char) * (length + 1));
	if (errno_msg == 0)
	{
		free(errno_msg);
		free(ver_str);
		return (NULL);
	}
	strcpy(errno_msg, datast->av[0]);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, ver_str);
	_strcat(errno_msg, ": ");
	_strcat(errno_msg, datast->args[0]);
	_strcat(errno_msg, ": Permission denied\n");
	_strcat(errno_msg, "\0");
	free(ver_str);
	return (errno_msg);
}
