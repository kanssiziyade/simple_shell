#include "shell.h"
/**
* tokenizer - function the commands execute
* @input_line: commands argument
* Return: NULL or status
**/
char **tokenizer(char *input_line)
{
char *token = NULL, *temp_str = NULL;
char **token_array = NULL;
int count = 0, index = 0;
if (!input_line)
{
return (NULL);
}
/* Duplicate the input line */
temp_str = strdup(input_line);
/* Tokenize the duplicated line */
token = strtok(temp_str, CUSTOM_DELIM);
if (token == NULL)
{
/* Free memory and return NULL if no tokens found */
input_line = NULL;
free(temp_str);
temp_str = NULL;
return (NULL); }
while (token)
{
count++;
token = strtok(NULL, CUSTOM_DELIM); }
free(temp_str);
temp_str = NULL;
token_array = malloc(sizeof(char *) * (count + 1));
if (!token_array)
{
input_line = NULL;
return (NULL); }
token = strtok(input_line, CUSTOM_DELIM);
while (token)
{
token_array[index] = strdup(token);
token = strtok(NULL, CUSTOM_DELIM);
index++; }
input_line = NULL;
token_array[index] = NULL;
return (token_array); }
