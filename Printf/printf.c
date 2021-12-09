#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int ft_putchar(char c)
{
	write(1, &c, 1);
	return(1);
}

int is_string(char *s)
{
	int i = 0;

	if (!s)
		s = "(null)";
	while (s[i])
		ft_putchar(s[i++]);
	return(i);
}	

int hex_num(unsigned int num, int base)
{
	int count = 0, i;
	char dec[] = "0123456789";
	char hex[] = "0123456789abcdef";

	if (num / base != 0)
		count += hex_num(num / base, base);
	i = num % base;
	if (base == 16)
		count += write(1, &hex[i], 1);
	if (base == 10)
		count += write(1, &dec[i], 1);
	return(count);
}

int ConvPush_num(int num)
{
	int count = 0;

	if (num < 0)
	{
		num *= -1;
		count += ft_putchar('-');
	}
	count += hex_num(num, 10);
	return (count);
}

int ft_printf(const char *format, ...)
{
	int	i = 0, count = 0;
	va_list args;
	
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
				count += is_string(va_arg(args, char *));
			if (format[i] == 'd')
				count += ConvPush_num(va_arg(args, int));
			if (format[i] == 'x')
				count += hex_num(va_arg(args, unsigned int), 16);
			//if (format[i] == '%')
			//	count += ft_putchar(format[i]);
		}
		else 
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int main()
{
	int num = -90;
	char name[] = "john";
	unsigned int hexa = 0xE7E55;
	unsigned int addy = (unsigned int)&num;
	
	printf("my name is %s, i am %d, and live at %x and %x andd %%", name, num, hexa, addy);
	printf("\n\n");
	ft_printf("my name is %s, i am %d, and live at %x and %x andd %%", name, num, hexa, addy);
	printf("\n\n");

	return (0);
}
