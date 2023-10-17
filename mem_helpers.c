#include "main.h"

unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
void free_buffer(buffer_t *output);
buffer_t *init_buffer(void);

/**
 * _memcpy - This will Copy n bytes from memory area src to the buffer
 * contained in buffer_t struct.
 * @output: Buffer_t struct.
 * @src: A pointer to memory area source to copy from.
 * @n: Bytes to be copied.
 *
 * Return: Number of bytes copied.
 */

unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
	{
		*(output->buffer) = *(src + index);
		(output->len)++;

		if (output->len == 1024)
		{
			write(1, output->start, output->len);
			output->buffer = output->start;
			output->len = 0;
		}

		else
			(output->buffer)++;
	}

	return (n);
}

/**
 * free_buffer - Frees a buffer_t struct.
 * @output: The buffer_t struct to be freed.
 */

void free_buffer(buffer_t *output)
{
	free(output->start);
	free(output);
}

/**
 * init_buffer - Initializes variable of struct type buffer_t.
 * Takes no arguments
 * Return: Initialized buffer_t pointer.
 */

buffer_t *init_buffer(void)
{
	buffer_t *output;

	output = malloc(sizeof(buffer_t));
	if (output == NULL)
		return (NULL);

	output->buffer = malloc(sizeof(char) * 1024);
	if (output->buffer == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start = output->buffer;
	output->len = 0;

	return (output);
}
