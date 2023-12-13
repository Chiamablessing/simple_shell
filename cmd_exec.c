#include "shell.h"

/**
 * colon_cdir -  function that checks if the current character
 * is a colon in the given path.
 * @path: a pointer to a character array representing the path.
 * @i: a pointer to an integer representing the current index in the path.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int colon_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] && path[*i] != ':')
	{
		*i += 1;
	}

	if (path[*i])
		(*i)++;

	return (0);
}

/**
 * _locate - function that locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_locate(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (colon_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 *
 * @datast: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_executable(data_shell *datast)
{
	struct stat st;
	int i;
	char *input;

	input = datast->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(datast, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if user has permissions to access the error
 *
 * @dir: destination directory
 * @datast: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_error_cmd(char *dir, data_shell *datast)
{

	shell_exit(datast);

	if (dir == NULL)
	{
		get_error(datast, 127);
		return (1);
	}

	if (_strcmp(datast->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{

			get_error(datast, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datast->args[0], X_OK) == -1)
		{
			get_error(datast, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - executes command lines
 *
 * @datast: data relevant (args and input)
 * Return: 1 on success.
 */
int cmd_exec(data_shell *datast)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void)wpd;

	exec = is_executable(datast);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _locate(datast->args[0], datast->_environ);
		if (check_error_cmd(dir, datast) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _locate(datast->args[0], datast->_environ);
		else
			dir = datast->args[0];
		execve(dir + exec, datast->args, datast->_environ);
	}
	else if (pd < 0)
	{
		perror(datast->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datast->status = state / 256;
	return (1);
}
