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
    int     j;

    i = 0;
    j = 0;
    while (str[i] && str[i] != '\n')
        i++;
    //hna drtha hde chek f7ala ila ml9itch '\n'dans str <==>(staric)reserve donc hada howa akhire line mkich 3lach n9at3o donc 4asni ndire lih free 
    if (str[i] == '\0')
    {
        free(str);
        return (NULL);
    }
    //ft_strlen(str) - i: blan hna howa i raha wa9fa 3la '\n' supose ligne fiha 17 caractere o i kifa f index 10  7ite i ktw9fe fach ktl9a '\0'
    //donc len = 17 - 10 => 7(hadi raj fiha case dyal '\0' dak ch 3lach mdrnach + 1)
    result = (char *)malloc(ft_strlen(str) - i);
    if (!result)
        return (NULL);
    i++;
    while (str[i])
        result[j++] = str[i++];
    result[j] = '\0';
    // hna kan free hit sf 3amarte result donc mkinch 3lach nkhli dik str
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
    len = i + 1;// hna bach nzide '\n'
    result = (char *)malloc(len + 1);// +1 3la 7sab n2ajouter '\0'
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
    // hna kan 7ote resulta jdida f temp li howa variable locale o kan free dak reserve l9dime pour eviter leaks
    temp = ft_strjoin(reserve, buf);
    free(reserve);
    return (temp);
}

char    *ft_lecteur(int fd, char *reserve)
{
    int     nbr;
    char    *buf;
    //ona inistalier hde resrve b une cahine vide pour eviter segmentaion fault f2awale dkhla 
    if (!reserve)
        reserve = ft_strdup("");// n9dro ndiro ft_caloc(1,1) nfse haja
    buf = ft_calloc(BUF_SIZE + 1, sizeof(char));
    while ((nbr = read(fd, buf, BUF_SIZE)) > 0)
    {
        buf[nbr] = '\0';
        reserve = free_join(reserve, buf);
        if (ft_strchr(buf, '\n'))
            break;
    }
    if (nbr < 0 || (!nbr && !*reserve))
    {
        free(reserve);
        reserve = NULL;
        return (NULL);
    }
    // hna kan freyiw bfre 7ite toujour kt7te fihe valeure 5ra donc pour eviter leaks
    free(buf);
    return (reserve);
}


char *ft_get_next_line(int fd)
{
    static char    *reserve;
    char           *line;

    if (BUF_SIZE <= 0 || fd < 0)
        return (NULL);
    reserve = ft_lecteur(fd,reserve);
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
    char *line_2 = ft_get_next_line(fd);
    // char *line_3 = ft_get_next_line(fd);
    // char *line_4 = ft_get_next_line(fd);
    // char *line_5 = ft_get_next_line(fd);
    // char *line_6 = ft_get_next_line(fd);
    printf("Ligne %d :%s", ++i,  line_1);
    printf("Ligne %d :%s", ++i,  line_2);
    // printf("Ligne %d :%s", ++i,  line_3);
    // printf("Ligne %d :%s", ++i,  line_4);
    // printf("Ligne %d :%s", ++i,  line_5);
    free(line_1);
    free(line_2);
    // free(line_3);
    // free(line_4);
    close(fd);
    atexit(mh);
    return (0);
}
