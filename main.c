#include "shell.h"
int main(void)
{
char *line_zyad = NULL, **zyad_command = NULL;
char *zyad_path = getenv("PATH");
int zyad_status = 0;
char *path_dorigine = strdup(zyad_path);
int z;
while (1) 
{
pid_t zyad_pid;
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
for (z = 0; zyad_command[z] != NULL; z++)
{
free(zyad_command[z]);  }
free(zyad_command);
exit(zyad_status);  }
zyad_pid = fork();
if (zyad_pid == -1)
{
perror("fork");
free(line_zyad);
free(path_dorigine);
for (z = 0; zyad_command[z] != NULL; z++)
{
free(zyad_command[z]); }
free(zyad_command);
exit(EXIT_FAILURE); }
if (zyad_pid == 0)
{
setenv("PATH", path_dorigine, 1) ;
if (execvp(zyad_command[0], zyad_command) == -1)
{
fprintf(stderr,"%s: 1: %s: not found\n","./hsh",zyad_command[0]) ;
free(line_zyad) ;
free(path_dorigine) ;
for (z = 0; zyad_command[z] != NULL; z++)
{
free(zyad_command[z]) ; }
free(zyad_command) ;
exit(127); }
if (strcmp(zyad_command[0], "env") == 0)
{
execvp("env", zyad_command) ;
perror("execvp") ;
exit(1) ; }
} else
{
int storie;
wait(&storie) ;
if (WIFEXITED(storie))
{
zyad_status = WEXITSTATUS(storie); }
else
{
zyad_status = -1; }
for (z = 0; zyad_command[z] != NULL; z++)
{
free(zyad_command[z]); }
free(zyad_command) ;
free(line_zyad); } }
return 0; }
