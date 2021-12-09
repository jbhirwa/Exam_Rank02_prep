#include <unistd.h>
#include <stdlib.h>
#include "gnl.h"

int ft_strlen(const char *s)
{
    int i = 0;

    while (s[i])
        i++;
    return (i);
}

char    *ft_strjoin(const char *s1, const char *s2)
{
    char    *str;
    int     i = 0, j = 0;

    str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!str)
        return (NULL);
    while (s1[i])
        str[j++] = s1[i++];
	i = 0;
    while (s2[i])
        str[j++] = s2[i++];
    str[j] = '\0';
    return (str);
}

char    *ft_substr(const char *str, int start, int len)
{
    char *substr;
    int i = 0;
    int j = 0;

    substr = (char *)malloc(sizeof(char) * len + 1);
    if (!substr)
        return (NULL);
    while (str[i])
    {
        if (i >= start && j < len)
            substr[j++] = str[i];
        i++; 
    }
    substr[j] = '\0';
    return (substr);
}

char    *ft_strchr(const char *s, int c)
{
    if (!c)
        return ((char *)s);
    while (*s)
    {
        if (*s == c)
            return ((char *)s);
        s++;
    }
    return (NULL);
}

static char *find_newline(int fd, char *buffer, char *remainder)
{
    int bytes_read = 1;
    char    *temp;

    while (bytes_read != 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)   
            return NULL;
        if (bytes_read == 0)
            break ;
        buffer[bytes_read] = '\0';
        if (!remainder)
            remainder = ft_substr(buffer, 0, bytes_read);
		temp = remainder;
        remainder = ft_strjoin(temp, buffer);
        free(temp);
        temp = NULL;
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    return (remainder);
}

static char *extract_line(char *line)
{
    char    *remainder;
    int     idx = 0;

    while (line[idx] != '\0' && line[idx] != '\n')
        idx++;
    if (line[idx] == '\0' || line[1] == '\0')
        return (NULL);
    remainder = ft_substr(line, idx + 1, ft_strlen(line) - idx);
    if (!(*remainder))
    {
        free(remainder);
        remainder = NULL;
    }
    line[idx + 1] = '\0';
    return (remainder);
}

char    *get_next_line(int fd)
{
    char        *line;
    char        *buffer;
    static char *remainder;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (0);
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    line = find_newline(fd, buffer, remainder);
    free(buffer);
    buffer = NULL;
    if (!line)
        return (0);
    remainder = extract_line(line);
    return (line);
}
