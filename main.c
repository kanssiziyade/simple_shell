#include "shell.h"
int main(void)
{
char *line_zyad = NULL, **zyad_command = NULL;
char *path = getenv("PATH");
int zyad_status = 0;
char *path_dorigine = strdup(path);
int i;
while (1) 
{
pid_t child_pid;
if (isatty(STDIN_FILENO))
{
printf("$ ");
fflush(stdout); }
line_zyad = customread_line();
if (line_zyad == NULL) 
{
if (isatty(STDIN_FILENO))
{
printf("\n"); }
free(path_dorigine);
return zyad_status; }
zyad_command = mytokenizer(line_zyad);
if (!zyad_command)
{
free(line_zyad);
continue;}
if (strcmp(zyad_command[0],"exit") == 0)
{
free(line_zyad);
free(path_dorigine);
for (i = 0; zyad_command[i] != NULL; i++)
{
free(zyad_command[i]);  }
free(zyad_command);
exit(zyad_status);  }
child_pid = fork();
if (child_pid == -1)
{
perror("fork");
free(line_zyad);
free(path_dorigine);
for (i = 0; zyad_command[i] != NULL; i++)
{
free(zyad_command[i]); }
free(zyad_command);
exit(EXIT_FAILURE); }
if (child_pid == 0)
{
setenv("PATH", path_dorigine, 1) ;
if (execvp(zyad_command[0], zyad_command) == -1)
{
fprintf(stderr,"%s: 1: %s: not found\n","./hsh",zyad_command[0]) ;
free(line_zyad) ;
free(path_dorigine) ;
for (i = 0; zyad_command[i] != NULL; i++)
{
free(zyad_command[i]) ; }
free(zyad_command) ;
exit(127); }
if (strcmp(zyad_command[0], "env") == 0)
{
execvp("env", zyad_command) ;
perror("execvp") ;
exit(1) ; }
} else
{
int status;
wait(&status) ;
if (WIFEXITED(status))
{
zyad_status = WEXITSTATUS(status); }
else
{
zyad_status = -1; }
for (i = 0; zyad_command[i] != NULL; i++)
{
free(zyad_command[i]); }
free(zyad_command) ;
free(line_zyad); } }
return 0; }
