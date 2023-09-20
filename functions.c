#include "main.h"

// PRINT CHARACHTER 

/**
 * print_char - a function that Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int output_flags, int output_width, int outpu_precision, int osize)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
// PRINT A STRING
/**
 * print_string - a fun that Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, a;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - length; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
//PRINT PERCENT SIGN
/**
 * print_percent - a fun that Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int output_flags, int outpu_width, int output_precision, int output_size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(output_flags);
	UNUSED(output_width);
	UNUSED(output_precision);
	UNUSED(output_size);
	return (write(1, "%%", 1));
}

//PRINT INT
/**
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int output_flags, int output_width, int output_precision, int output_size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int m = va_arg(types, long int);
	unsigned long int num;

	m = convert_size_number(n, size);

	if (m == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)m;

	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_number(is_negative, a, buffer, output_flags, output_width, output_precision, output_size));
}

//PRINT BINARY
/**
 * print_binary - a fun that Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int m, b, a, sum;
	unsigned int n[32];
	int count;

	UNUSED(buffer);
	UNUSED(output_flags);
	UNUSED(output_width);
	UNUSED(output_precision);
	UNUSED(output_size);

	m = va_arg(types, unsigned int);
	b = 2147483648; /* (2 ^ 31) */
	n[0] = m / b;
	for (a = 1; a < 32; a++)
	{
		m /= 2;
		n[i] = (m / b) % 2;
	}
	for (a = 0, sum = 0, count = 0; a < 32; a++)
	{
		sum += n[i];
		if (sum || a == 31)
		{
			char h = '0' + n[i];

			write(1, &h, 1);
			count++;
		}
	}
	return (count);
}
