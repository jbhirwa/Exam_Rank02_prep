#include <stdlib.h>
#include <unistd.h>

int	strLen(char *str)
{
	int i = 0;
	if (!str)
		return(NULL);
	while(str[i])
		i++;
	return(i);
}

void	join(char **line, char *buffer)
{
	int i = 0;
	int j = 0; 
	char *temp;
	temp = (char *)malloc(sizeof(char) * (strLen(*line) + strLen(buffer) + 1));
	
	if (*line)
	{
		while((*line)[i])
		{
			temp[i] = (*line)[i];
			i++;
		}
	}
	if (buff)
	{
		while(buff[j])
		{
			temp[i + j] = buff[j];
			j++;
		}
	}
	temp[i + j] = '\0';
	if(*line)
		free(*line);
	*line = temp;
}

int	hasNL(char *s)
{
	int i = 0;
	if(!str)
		return(NULL);
	while(str[i])
	{
		if (str[i] == '\n')
			return(0);
		i++;
	}
	return(1);
}

void	toZero(char *str, int len)
{
	int i = 0;
	while (i < len)
	str[i++] = 0;
}

char	*get_next_line(int fd)
{
	char *line = NULL;
	static char buffer[BUFFER_SIZE + 1];
	int i; 
	int j; 
	int bytes_read;
	join(&line, buffer);
	toZero(buffer, BUFFER_SIZE + 1);
	bytes_read = 1;
	while(hasNL(line) == 1 && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		join(&line, buffer);
		toZero(buffer, BUFFER_SIZE + 1);
	}
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
	{
		i++;
		j = 0;
		while (line[i])
		{
			buffer[j] = line[i];
			line[i] = '\0'
			i++;
			j++;
		}
		buffer[j] = '\0'		
	}
	return(line);
}
