#include "shell.h"

/**
 * execute_command - function to execute a command
 * @cmd_array: The array containing the command and its arguments
 * @args_array: The array containing the arguments
 * Return: return the status or NULL
 */
int execute_command(char **cmd_array, char **args_array)
{
    int index;
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == 0)
    {
        if (execve(cmd_array[0], cmd_array, environ) == -1)
        {
            perror(args_array[0]);
            for (index = 0; cmd_array[index]; index++)
            {
                free(cmd_array[index]);
                cmd_array[index] = NULL;
            }
            free(cmd_array);
            cmd_array = NULL;
            exit(0);
        }
    }
    else
    {
        waitpid(child_pid, &status, 0);
        for (index = 0; cmd_array[index]; index++)
        {
            free(cmd_array[index]);
            cmd_array[index] = NULL;
        }
        free(cmd_array);
        cmd_array = NULL;
    }
    return (WEXITSTATUS(status));
}
