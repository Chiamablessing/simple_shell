#include "shell.h"

/**
 * cd_dr - function that changes current directory
 *
 * @datast: data relevant
 * Return: 1 on success
 */
int cd_dr(data_shell *datast)
{
	char *dir;
	int ishome, ishome2, isddast;

	dir = datast->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddast = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddast)
	{
		cd_to_home(datast);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datast);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_do(datast);
		return (1);
	}

	cd_to(datast);

	return (1);
}
