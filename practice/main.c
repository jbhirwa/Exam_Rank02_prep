#include "gnl.h"
#include <fcntl.h>
#include <stdio.h>
/*
 * gcc main.c gnl.c test.txt
 */

int main(void)
{
    int     fd;
    char    *str;

    fd = open("test.txt", O_RDWR);
    str = get_next_line(fd);
    while (str != NULL)
    {
        printf("%s", str);
        str = get_next_line(fd);
    }
    
    return (0);
}
