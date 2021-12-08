#include "gnl.h"

int ft_strlen(const char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char *strchr(const char *s, int c)
{
	char *str;

	if (!s)
		return (NULL);
	str = (char *)s;
	while (*str && *str != (unsigned char)c)
		str++;
	if (*str == (unsigned char)c)
		return (str);
	return (NULL);
}

char	*substr(char *buffer, unsigned int start, size_t len)
{
	char	*sub;
	size_t		i;
	
	if (!buffer)
		return (NULL);
	i = ft_strlen(buffer);
	if (len > i)
		len = i;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (buffer[start + i] && (start + i) < len)
	{
		sub[i] = buffer[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char *strjoin(char *s1, char *s2)
{
	
	int i = 0, j = 0;
	char *s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s3)
		return(NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	//free(s1);
	s3[j] = '\0';
	return (s3);
}

char	*extract_leftover(char *leftover, int *nl_index)
{
	char *tail;

	tail = substr(leftover, *nl_index + 1, ft_strlen(leftover));
	free(leftover);
	return (tail);
}

char	*extract_line(char *leftover, int *nl_index)
{
	int i = 0;
	char *line;

	while (leftover[i] && leftover[i] != '\n')
		i++;
	*nl_index = i;
	line = substr(leftover, 0, i + 1);
	return (line);
}

char	*find_nextline(int fd, char *leftover)
{
	int bytes_read = 1;
	char buffer[BUFFER_SIZE + 1];

	while (bytes_read > 0 && !strchr(leftover, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		if (!leftover)
			leftover = substr(buffer, 0, bytes_read);
		else
			leftover = strjoin(buffer, leftover);
	}
	return (leftover);
}

char *get_next_line(int fd)
{
	int			nl_index = 0;
	char		*line;
	static char	*leftover;
	
	if (fd < 0 || BUFFER_SIZE < 1 || (read(fd, 0, 0) < 0))
		return (NULL);
	leftover = find_nextline(fd, leftover);
	if (!leftover)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line = extract_line(leftover, &nl_index);
	leftover = extract_leftover(leftover, &nl_index);
	return (line);
}
