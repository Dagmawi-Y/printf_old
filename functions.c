#include "main.h"

// Print a character
/**
 * print_char - a function that prints a character to the output buffer
 *
 * @input_types: List of arguments
 * @output_buffer: Buffer array to handle print
 * @output_flags:  Calculates active flags
 * @output_width: Width
 * @output_precision: Precision specification
 * @output_size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list input_types, char output_buffer[],
	int output_flags, int output_width, int output_precision, int output_size)
{
	char c = va_arg(input_types, int);

	return (handle_write_char(c, output_buffer, output_flags, output_width, output_precision, output_size));
}

// PRINT A STRINGS

/**
 * print_string - a function that prints a string to the output buffer
 *
 * @input_types: List of arguments
 * @output_buffer: Buffer array to handle print
 * @output_flags:  Calculates active flags
 * @output_width: get width.
 * @output_precision: Precision specification
 * @output_size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list input_types, char output_buffer[],
	int output_flags, int output_width, int output_precision, int output_size)
{
	int length = 0, a;
	char *str = va_arg(input_types, char *);

	UNUSED(output_buffer);
	UNUSED(output_flags);
	UNUSED(output_width);
	UNUSED(output_precision);
	UNUSED(output_size);
	if (str == NULL)
	{
		str = "(null)";
		if (output_precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (output_precision >= 0 && output_precision < length)
		length = output_precision;

	if (output_width > length)
	{
		if (output_flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (a = output_width - length; a > 0; a--)
				write(1, " ", 1);
			return (output_width);
		}
		else
		{
			for (a = output_width - length; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (output_width);
		}
	}

	return (write(1, str, length));
}

//PRINT PERCENT SIGN 

/**
 * print_percent - a function that prints a percent sign to the output buffer
 *
 * @input_types: List of arguments
 * @output_buffer: Buffer array to handle print
 * @output_flags:  Calculates active flags
 * @output_width: get width.
 * @output_precision: Precision specification
 * @output_size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list input_types, char output_buffer[],
	int output_flags, int output_width, int output_precision, int output_size)
{
	UNUSED(input_types);
	UNUSED(output_buffer);
	UNUSED(output_flags);
	UNUSED(output_width);
	UNUSED(output_precision);
	UNUSED(output_size);
	return (write(1, "%%", 1));
}

//PRINT INT

/**
 * print_int - a function that prints an integer to the output buffer
 *
 * @input_types: List of arguments
 * @output_buffer: Buffer array to handle print
 * @output_flags:  Calculates active flags
 * @output_width: get width.
 * @output_precision: Precision specification
 * @output_size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list input_types, char output_buffer[],
	int output_flags, int output_width, int output_precision, int output_size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(input_types, long int);
	unsigned long int my_num;

	n = convert_size_number(n, output_size);

	if (n == 0)
		output_buffer[a--] = '0';

output_buffer[BUFF_SIZE - 1] = '\0';
	my_num = (unsigned long int)n;

	if (n < 0)
	{
		my_num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (my_num > 0)
	{
		output_buffer[a--] = (my_num % 10) + '0';
		my_num /= 10;
	}

	a++;

	return (write_number(is_negative, a, output_buffer, output_flags, output_width, output_precision, output_size));
}	
//PRINT BINARY
/**
 * print_binary - Prints an unsigned number in binary.
 *
 * @types: List of arguments.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Get width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of chars printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n = va_arg(types, unsigned int);
	unsigned int mask = 1 << 31;
	int count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	while (mask) {
		char c = '0' + (n & mask ? 1 : 0);
		write(1, &c, 1);
		count++;
		mask >>= 1;
	}

	return count;
}
