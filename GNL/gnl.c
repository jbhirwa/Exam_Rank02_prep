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
	int		i = 0;
	int		j = 0;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s3)
		return (NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	//free(s1);
	s3[j] = '\0';
	return (s3);
}

char	*extract_leftover(char *tail, int *n)
{
	char	*str;

	str = ft_substr(tail, *n + 1, ft_strlen(tail));
	free(tail);
	return (str);
}

char	*extract_newline(char *tail, int *n)
{
	int		i;
	char	*line;

	i = 0;
	while (tail[i] != '\n' && tail[i])
		i++;
	line = ft_substr(tail, 0, i + 1);
	*n = i;	// i holds the index to which /n is found, i index is assigned to n
	return (line);
}

char	*find_newline(int fd, char *tail)
{
	int		count_read;
	char	buf[BUFFER_SIZE + 1];	
	
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
	static char	*tail;	
	char		*line; 

	if (fd < 0 || BUFFER_SIZE < 1 || (read(fd, 0, 0) < 0))
		return (NULL);
	tail = find_newline(fd, tail);
	if (!tail[0])
	{
		free(tail);
		tail = NULL;
		return (NULL);
	}
	n = 0;
	line = extract_newline(tail, &n);
	tail = extract_leftover(tail, &n);
	return (line);
}
