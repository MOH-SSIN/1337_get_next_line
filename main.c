#include "get_next_line.h"

int main()
{
    int fd = open("yasser.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("erreur\n");
        return (1);
    }

    int i = 1;
    char *line;
    while ((line = ft_get_next_line(fd)))
    {
        printf("Ligne %d : %s", i++, line);
    }
    free(line);
    close(fd);
    return (0);
}