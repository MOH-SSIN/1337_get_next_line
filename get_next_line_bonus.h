#ifndef GET_NEXT_LIGNE_BONUS_H
#define GET_NEXT_LIGNE_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10000000
#endif
#define FILE_D_MAX 100
static char *reserve[FILE_D_MAX];

char	*get_next_line(int fd);
size_t  ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
#endif