/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:56:07 by mez-zahi          #+#    #+#             */
/*   Updated: 2024/11/14 20:24:17 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char *ft_cut_reste(char *str)
{
    char    *result;
    int     i;
    int     len;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\0')//Objectif : Cette condition vérifie si str est arrivé à la fin ('\0') sans rencontrer de \n. Si c’est le cas, cela signifie qu’il n’y a plus de contenu restant pour le prochain appel, et ft_cut_reste retourne NULL pour signaler que la lecture est terminée.
    {
        free(str);
        return (NULL);
    }
    len = i + 2;
    result = (char *)malloc(len);
    if (!result)
        return (NULL);
    i = -1;
    while (++i < len)
        result[i] = str[i];
    result[i] = '\0';
    free(str);
    return (result);   
}

char *ft_cut_line(char *str)
{
    char *result;
    int i = 0;
    int len;

    while (str[i] && str[i] != '\n')
        i++;
    len = i + 1;
    result = (char *)malloc(len + 1);
    if (!result)
        return (NULL);
    i = -1;
    while (++i < len)
        result[i] = str[i];
    result[i] = '\0';
    return (result);
}

char    *free_join(char *reserve, char *buf)
{
    char    *temp;

    temp = ft_strjoin(reserve, buf);
    free(reserve);
    return (temp);
}

char    *ft_lecteur(int fd)
{
    char    *buffer_als;
    int     nbr;
    char    buf[BUF_SIZE];

    buffer_als = ft_strdup("");
    while ((nbr = read(fd, buf, BUF_SIZE )) > 0)
    {
        buf[nbr] = '\0';
        buffer_als = free_join(buffer_als, buf);
        // printf("\n\n\n[%p\n]\n\n\n",buffer_als);
        if (ft_strchr(buf, '\n'))
            break;
    }
    if (nbr < 0 || (!nbr && !*buffer_als))
    {
        free(buffer_als);
        buffer_als = NULL;
        return (NULL);
    }
    return (buffer_als);
}


char *ft_get_next_line(int fd)
{
    static char    *reserve;
    char           *line;

    if (BUF_SIZE <= 0 || fd < 0)
        return (NULL);
    reserve = ft_lecteur(fd);
    if (!reserve)
        return (NULL);
    line = ft_cut_line(reserve);
    reserve = ft_cut_reste(reserve);
    return (line);
}

void mh()
{
    system("leaks a.out");
}

int main()
{
    int fd = open("mohcine.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("erreur\n");
        return (1);
    }
    int i = 0;
    char *line_1 = ft_get_next_line(fd);
    // char *line_2 = ft_get_next_line(fd);
    // char *line_3 = ft_get_next_line(fd);
    // char *line_4 = ft_get_next_line(fd);
    // printf("Ligne %d : %s", ++i,  line_1);
    // printf("Ligne %d : %s", ++i,  line_2);
    // printf("Ligne %d : %s", ++i,  line_3);
    // printf("Ligne %d : %s", ++i,  line_4);
    free(line_1);
    // free(line_2);
    // free(line_3);
    // free(line_4);
    close(fd);
    atexit(mh);
    return (0);
}
