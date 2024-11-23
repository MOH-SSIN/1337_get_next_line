#include "get_next_line_bonus.h"


char *ft_cut_reste(char *str) {
    char *result;
    int i = 0;
    int j = 0;

    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\0') {
        free(str);
        return NULL;
    }
    result = (char *)malloc(ft_strlen(str) - i);
    if (!result)
        return NULL;
    i++;
    while (str[i])
        result[j++] = str[i++];
    result[j] = '\0';
    free(str);
    return result;
}

char *ft_cut_line(char *str) {
    char *result;
    int i = 0;
    int len;

    while (str[i] && str[i] != '\n')
        i++;
    len = i + 1;
    result = (char *)malloc(len + 1);
    if (!result)
        return NULL;
    i = -1;
    while (++i < len)
        result[i] = str[i];
    result[i] = '\0';
    return result;
}

char *free_join(char *reserve, char *buf) {
    char *temp = ft_strjoin(reserve, buf);
    free(reserve);
    return temp;
}

char *ft_lecteur(int fd, char *reserve) {
    int nbr;
    char *buf;

    if (!reserve)
        reserve = ft_strdup("");
    buf = ft_calloc(BUF_SIZE + 1, sizeof(char));
    while ((nbr = read(fd, buf, BUF_SIZE)) > 0) {
        buf[nbr] = '\0';
        reserve = free_join(reserve, buf);
        if (ft_strchr(buf, '\n'))
            break;
    }
    free(buf);
    if (nbr < 0 || (!nbr && !*reserve)) {
        free(reserve);
        return NULL;
    }
    return reserve;
}

char *ft_get_next_line(int fd) {
    char *line;

    if (BUF_SIZE <= 0 || fd < 0 || fd >= FILE_D_MAX)
        return NULL;

    // Lecture et récupération de la ligne pour ce `fd`
    reserve[fd] = ft_lecteur(fd, reserve[fd]);
    if (!reserve[fd])
        return NULL;

    // Découpage de la ligne et mise à jour de `reserve[fd]`
    line = ft_cut_line(reserve[fd]);
    reserve[fd] = ft_cut_reste(reserve[fd]);

    // Si `reserve[fd]` est vide après extraction, libérer la mémoire
    if (!reserve[fd]) {
        free(reserve[fd]);
        reserve[fd] = NULL;
    }
    return line;
}

// Fonction de test pour détecter les fuites de mémoire
void mh() {
    system("leaks a.out");
}

int main() {
    int fd_1 = open("mohcine.txt", O_RDONLY);
    if (fd_1 == -1) {
        printf("erreur\n");
        return 1;
    }
    int fd_2 = open("yaser.txt", O_RDONLY);
    if (fd_2 == -1) {
        printf("erreur\n");
        return 1;
    }

    char *line_1 = ft_get_next_line(fd_1);
    char *line_2 = ft_get_next_line(fd_2);
    printf("Ligne 1 :%s", line_1);
    printf("Ligne 2 :%s", line_2);
    free(line_1);
    free(line_2);
    close(fd_1);
    close(fd_2);
    atexit(mh);
    return 0;
}
