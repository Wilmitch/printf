#include "main.h"

unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output,
		unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

/**
 * convert_sbase - Will convert a signed long to an inputted base and stores
 *                 the result to a buffer contained in a struct.
 * @output: The buffer_t struct containing a character array.
 * @num: The signed long to be converted.
 * @base: Pointer to the string containing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: Width modifiers.
 * @prec: Precision modifier.
 *
 * Return: Number of bytes stored in the buffer.
 */

unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	int size;
	char digit, pad = '0';
	unsigned int ret = 1;

	for (size = 0; *(base + size);)
		size++;

	if (num >= size || num <= -size)
		ret += convert_sbase(output, num / size, base,
				flags, wid - 1, prec - 1);

	else
	{
		/* Handles precision */
		for (; prec > 1; prec--, wid--)
			ret += _memcpy(output, &pad, 1);

		/* Handles the width */
		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
	}

	digit = base[(num < 0 ? -1 : 1) * (num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}

/**
 * convert_ubase - Converts an unsigned long to an inputted base and then
 *                 stores the result to a buffer contained in a struct.
 * @output: A buffer_t struct containing a character array.
 * @num: An unsigned long to be converted.
 * @base: Pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: Width modifiers.
 * @prec: Precision modifier.
 *
 * Return: Number of bytes stored to the buffer.
 */

unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	unsigned int size, ret = 1;
	char digit, pad = '0', *lead = "0x";

	for (size = 0; *(base + size);)
		size++;

	if (num >= size)
		ret += convert_ubase(output, num / size, base,
				flags, wid - 1, prec - 1);

	else
	{
		/* Printing the pointer address */
		if (((flags >> 5) & 1) == 1)
		{
			wid -= 2;
			prec -= 2;
		}
		/* Handles precision */
		for (; prec > 1; prec--, wid--)
			ret += _memcpy(output, &pad, 1);

		/* Handle the width */
		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
		/* Print 0x for the pointer address */
		if (((flags >> 5) & 1) == 1)
			ret += _memcpy(output, lead, 2);
	}

	digit = base[(num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}
