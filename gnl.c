size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	new_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s) || !len)
		return (ft_strdup(""));
	new_len = ft_strlen(s + start);
	if (new_len < len)
		len = new_len;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (src == NULL || dst == NULL)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	size_t	i;

	i = 0;
	duplicate = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (duplicate == NULL)
		return (NULL);
	while (s[i])
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (0);
}

static char	*extract_newline(char *line)
{
	char	*leftover;
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	leftover = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*leftover == '\0')
	{
		free(leftover);
		leftover = NULL;
	}
	line[i + 1] = '\0';
	return (leftover);
}

static char	*find_newline(int fd, char *buffer, char *backup)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backup;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buffer)
		return (NULL);
	line = find_newline(fd, buffer, backup);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (line);
	backup = extract_newline(line);
	return (line);
}
