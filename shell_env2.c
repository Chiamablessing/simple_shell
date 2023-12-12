#include "shell.h"

/**
 * copy_info - function that copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	/*free(new);*/
	return (new);
}

/**
 * set_env - function that sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datast: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *datast)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datast->_environ[i]; i++)
	{
		var_env = _strdup(datast->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datast->_environ[i]);
			datast->_environ[i] = copy_info(name_env, value);
			free(var_env);
			/*free(name_env);*/
			return;
		}
		free(var_env);
	}

	datast->_environ = _reallocdp(datast->_environ, i, sizeof(char *) * (i + 2));
	datast->_environ[i] = copy_info(name, value);
	datast->_environ[i + 1] = NULL;
}

/**
 * _setenv - function that compares env variables names
 * with the name passed.
 * @datast: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datast)
{

	if (datast->args[1] == NULL || datast->args[2] == NULL)
	{
		get_error(datast, -1);
		return (1);
	}

	set_env(datast->args[1], datast->args[2], datast);

	return (1);
}

/**
 * _unsetenv - function that deletes a environment variable
 *
 * @datast: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datast)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (datast->args[1] == NULL)
	{
		get_error(datast, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datast->_environ[i]; i++)
	{
		var_env = _strdup(datast->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datast->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datast, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datast->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datast->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datast->_environ[k]);
	free(datast->_environ);
	datast->_environ = realloc_environ;
	/*free(realloc_environ);*/
	return (1);
}
