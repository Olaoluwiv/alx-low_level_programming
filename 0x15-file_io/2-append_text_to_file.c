#include "main.h"

/**
 * append_text_file - Appends text at the end of a file.
 * @filename: File name.
 * @text_content: Content to be added.
 *
 * Return: 1 if successful, -1 if fails.
 */
int append_text_file(const char *filename, char *text_content)
{
int file_d;
int nletters;
ssize_t rwr;

if (!filename)
return (-1);

file_d = open(filename, O_WRONLY | O_APPEND);
if (file_d == -1)
return (-1);

if (text_content)
{
for (nletters = 0; text_content[nletters]; nletters++)
;

rwr = write(file_d, text_content, nletters);
if (rwr == -1)
{
close(file_d);
return (-1);
}
}

close(file_d);
return (1);
}
