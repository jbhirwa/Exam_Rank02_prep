#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

# include <stdio.h>		// для функции main
# include <fcntl.h>		// для функции open
# include <stdlib.h>	// для функции malloc
# include <unistd.h>	// для остальных функций
# define BUFFER_SIZE 10

char	*get_next_line(int fd);

#endif
