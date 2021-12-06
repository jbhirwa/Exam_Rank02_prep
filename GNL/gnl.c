#include "gnl.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	while (*str && *str != (unsigned char)c)
		str++;
	if (*str == (unsigned char)c)
		return (str);
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (i < len)
		len = i;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start + i] && (start + i) < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	j = -1;
	while (s2[++j])
		s3[i + j] = s2[j];
	free(s1);
	s3[i + j] = '\0';
	return (s3);
}

char	*ft_tail(char *tail, int *n)
{
	char	*str;

	str = ft_substr(tail, *n + 1, ft_strlen(tail));
	free(tail);
	return (str);
}

char	*ft_line(char *tail, int *n)
{
	int		i;
	char	*line;

	i = 0;
	while (tail[i] != '\n' && tail[i])
		i++;
	line = ft_substr(tail, 0, i + 1);
	*n = i;	// присваиваю индекс по которому расположен '\n'
	return (line);
}

char	*ft_read(int fd, char *tail)
{
	int		count_read;
	char	buf[BUFFER_SIZE + 1];	// выделяется память на стеке

	count_read = 1;
	while (count_read > 0 && !ft_strchr(tail, '\n'))
	{
		count_read = read(fd, buf, BUFFER_SIZE);
		if (count_read < 0)
			return (NULL);
		buf[count_read] = '\0';
		if (!tail)
			tail = ft_substr(buf, 0, count_read);
		else
			tail = ft_strjoin(tail, buf);
	}
	return (tail);
}

char	*get_next_line(int fd)
{
	int			n;
	static char	*tail;	// остаток считанного после '\n', который нуже для слудующего вызова GNL
	char		*line;	// строка которая будет возращатся GNL

	if (fd < 0 || BUFFER_SIZE < 1 || (read(fd, 0, 0) < 0))	// важная защита для BUFFER_SIZE < 1
		return (NULL);
	tail = ft_read(fd, tail);
	if (!tail[0])
	{
		free(tail);
		tail = NULL;
		return (NULL);
	}
	n = 0;
	line = ft_line(tail, &n);	// отправляю 'n' по адрусу, что бы работать с оригинальной переменной
	tail = ft_tail(tail, &n);	// здесь тоже
	return (line);
}
