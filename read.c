#include "shell.h"
#include <stdio.h>
/**
 *  * read_user_input - function for write a prompt
 *   *
 *    * Return: return custom_line or NULL
 *    */
char *read_user_input(void)
{
		char *line = NULL;
			size_t buffer_size = 0;
				ssize_t input_length;


					custom_length = getline(&line, &custom_buffer_size, stdin);

						if (custom_length == -1)
								{
										free(line);
											return (NULL);
												}
							return (line);
}
