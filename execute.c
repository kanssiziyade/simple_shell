#include "shell.h"
/**
 * executealternative - function for execute command
 * @commands_zyad: The first parameter
 * @arguments_zyad: the second parameter
 * Return: return status or NULL
*/
int executealternative(char **commands_zyad, char **arguments_zyad)
{
	int index;
	pid_t child_process;
	int status;

	child_process = fork();
	if (child_process == 0)
	{
		if (execve(commands_zyad[0], commands_zyad, environ) == -1)
		{
			perror(arguments_zyad[0]);
			for (index = 0; commands_zyad[index]; index++)
			{
				free(commands_zyad[index]), commands_zyad[index] = NULL;
			}
			free(commands_zyad), commands_zyad = NULL;
			exit(0);
		}
	}
	else
	{
		waitpid(child_process, &status, 0);
		for (index = 0; commands_zyad[index]; index++)
		{
			free(commands_zyad[index]);
			commands_zyad[index] = NULL;
		}
		free(commands_zyad);
		commands_zyad = NULL;
	}
	return (WEXITSTATUS(status));
}
