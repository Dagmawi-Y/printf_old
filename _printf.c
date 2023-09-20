#include "main.h"

void print_output_buffer(char output_buffer[], int *output_buffer_index);

/**
 * my_printf - Printf function
 * @format: format string.
 * Return: Printed chars.
 */
int my_printf(const char *format, ...)
{
	int a, printed = 0, printed_chars = 0;
	int flags, width, precision, size, output_buffer_index = 0;
	va_list list;
	char output_buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			output_buffer[output_buffer_index++] = format[a];
			if (output_buffer_index == BUFF_SIZE)
				print_output_buffer(output_buffer, &output_buffer_index);
			/* write(1, &format[a], 1);*/
			printed_chars++;
		}
		else
		{
			print_output_buffer(output_buffer, &output_buffer_index);
			flags = get_flags(format, &a);
			width = get_width(format, &a, list);
			precision = get_precision(format, &a, list);
			size = get_size(format, &a);
			++a;
			printed = handle_print(format, &a, list, output_buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_output_buffer(output_buffer, &output_buffer_index);

	va_end(list);

	return (printed_chars);
}

/**
 * print_output_buffer - Prints the contents of the output buffer if it exist
 * @output_buffer: Array of chars
 * @output_buffer_index: Index at which to add next char, represents the length.
 */
void print_output_buffer(char output_buffer[], int *output_buffer_index)
{
	if (*output_buffer_index > 0)
		write(1, &output_buffer[0], *output_buffer_index);

	*output_buffer_index = 0;
}
