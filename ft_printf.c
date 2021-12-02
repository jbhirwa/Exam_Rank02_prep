#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int ft_putstr(char *s)
{
    int i;

    i = 0;
    if (!s)
        s = "(null)";
    while (s[i])
        ft_putchar(s[i++]);
    return (i);
}

int ft_putnbr(unsigned int i, int base)
{
    char hex[] = "0123456789abcdef";
    char dec[] = "0123456789";
    int n;

    int count = 0;
    if (i / base != 0)
        count += ft_putnbr(i / base, base);
    n = i % base;
    if (base == 16)
        count += write(1, &hex[n], 1);
    else if (base == 10)
        count += write(1, &dec[n], 1);
    return (count);
}

int ft_printfd(int i)
{
    int count;

    count = 0;
    if (i < 0)
    {
        i *= -1;
        count += ft_putchar('-');
    }
    count += ft_putnbr(i, 10);
    return (count);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int i = 0, count = 0;
    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'd')
                count += ft_printfd(va_arg(args, int));
            if (format[i] == 's')
                count += ft_putstr(va_arg(args, char *));
            if (format[i] == 'x')
                count += ft_putnbr(va_arg(args, unsigned int), 16);
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
	int num = 5;
	char *str = "hello world!";
	char *lol = NULL;
	unsigned char xX = 0xC0;

	printf("\n\n%d\n\n\n", num);
	ft_printf("\n\n\n%d\n\n\n", num);

	printf("%s\n", str);
	ft_printf("%s\n", str);

	printf("%x\n", xX);
	ft_printf("%x\n", xX);
	printf("%X\n", xX);
	ft_printf("%X\n", xX);

	printf("%s\n", lol);
	ft_printf("%s\n", lol);


char    *name = "Sara";
    int     year = -2021;
    int     *place = &year;

    ft_printf("Hello there %s. 90%% of %d is over. Meet me at %x", name, year, place);

	printf("\n\n\n");

 	char	stri[] = "hello";
	int		numb = -90;
	int		hex = 0xE7E55;
	printf("hello, repeat: %s, repeat it %d times and %x", stri, numb, hex);
	printf("\n\n\n");
	ft_printf("hello, repeat: %s, repeat it %d times and %x", stri, numb, hex);
	printf("\n");
	return(0);
}
