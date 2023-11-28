#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


/**
 * create_file - Creates a file and writes content to it.
 * @filename: The name of the file to create.
 * @text_content: The content to write to the file.
 *
 * Return: 1 on success, -1 on failure.
 */
int create_file(const char *filename, char *text_content)
{
int file_d;
int nletters;
ssize_t rwr;

if (!filename)
return (-1);

file_d = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
if (file_d == -1)
return (-1);

if (!text_content)
text_content = "";

for (nletters = 0; text_content[nletters]; nletters++)

rwr = write(file_d, text_content, nletters);
if (rwr == -1)
{
close(file_d);
return (-1);
}

close(file_d);
return (1);
}
