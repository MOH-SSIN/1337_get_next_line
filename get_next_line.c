#include "get_next_line.h"


char *ft_nettoyage_1(char *str)
{
    char *result;
    int i = 0;
    int len;

    while (str[i] && str[i] != '\n')
        i++;
    len = i + 1;
    result = (char *)malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);
    i = -1;
    while (++i < len)
        result[i] = str[i];
    result[i] = '\0';

    return (result);
}

char *ft_nettoyage_2(char *str)
{
    char *result;
    int i;

    i = 0;
    while (*str && *str != '\n')
        str++;
    if (*str)
        str++;
    result = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!result)
        return (NULL);
    while (*str)
        result[i++] = *str++;
    result[i] = '\0';
    return (result);
}

char *ft_get_next_line(int fd)
{
    char buf[BUF_SIZE];
    static char *reserve;
    char *line;
    ssize_t nbr;

    if (!reserve)
        reserve = ft_strdup("");
    while ((nbr = read(fd, buf, BUF_SIZE - 1)) > 0)
    {
        buf[nbr] = '\0';
        reserve = ft_strjoin(reserve, buf);
        if (ft_strchr(buf, '\n'))
            break;
    }
    if (nbr < 0 || (!nbr && !*reserve))
    {
        free(reserve);
        return (NULL);
    }
    line = ft_nettoyage_1(reserve);
    reserve = ft_nettoyage_2(reserve);
    return (line);
}

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
