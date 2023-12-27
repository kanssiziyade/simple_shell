#include "shell.h"

int main(void)
{
char *text = NULL, **command_args = NULL;
char *path = getenv("PATH");
int alternative_status = 0;
char *original_path = strdup(path);
int i;
while (1) 
{
pid_t child_pid;
if (isatty(STDIN_FILENO))
{
printf("$ ");
fflush(stdout); }
text = custom_read_text();
if (text == NULL) 
{
if (isatty(STDIN_FILENO))
{
printf("\n"); }
free(original_path);
return alternative_status; }
command_args = my_tokenizer(text);
if (!command_args)
{
free(text);
continue;}
if (strcmp(command_args[0],"exit") == 0)
{
free(text);
free(original_path);
for (i = 0; command_args[i] != NULL; i++)
{
free(command_args[i]);  }
free(command_args);
exit(alternative_status);  }
child_pid = fork();
if (child_pid == -1)
{
perror("fork");
free(text);
free(original_path);
for (i = 0; command_args[i] != NULL; i++)
{
free(command_args[i]); }
free(command_args);
exit(EXIT_FAILURE); }
if (child_pid == 0)
{
setenv("PATH", original_path, 1) ;
if (execvp(command_args[0], command_args) == -1)
{
fprintf(stderr,"%s: 1: %s: not found\n","./hsh",command_args[0]) ;
free(text) ;
free(original_path) ;
for (i = 0; command_args[i] != NULL; i++)
{
free(command_args[i]) ; }
free(command_args) ;
exit(127); }
if (strcmp(command_args[0], "env") == 0)
{
execvp("env", command_args) ;
perror("execvp") ;
exit(1) ; }
} else
{
int status;
wait(&status) ;
if (WIFEXITED(status))
{
alternative_status = WEXITSTATUS(status); }
else
{
alternative_status = -1; }
for (i = 0; command_args[i] != NULL; i++)
{
free(command_args[i]); }
free(command_args) ;
free(text); } }
return 0; }
