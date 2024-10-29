#ifndef GET_NEXT_LIGNE_H
#define GET_NEXT_LIGNE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUF_SIZE 5

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(const char *s)
{
    char    *ptr;
    size_t  i;
    size_t  size;

    i = -1;
    size = ft_strlen(s);
    ptr = (char *)malloc(size + 1);
    if(!ptr)
        return(NULL);
    while(++i < size)
        ptr[i] = s[i];
    ptr[i] = '\0';
    return(ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1 || !s2 || !(ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return (( char *)s);
}

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

#endif