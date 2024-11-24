/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:59:41 by mez-zahi          #+#    #+#             */
/*   Updated: 2024/11/24 14:31:37 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_cut_reste(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	result = (char *)malloc(ft_strlen(str) - i);
	if (!result)
	{
		free(result);
		return (NULL);
	}
	i++;
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	free(str);
	return (result);
}

char	*ft_cut_line(char *str)
{
	char	*result;
	int		i;
	int		len;

	i = 0;
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

char	*free_join(char *reserve, char *buf)
{
	char	*temp;

	temp = ft_strjoin(reserve, buf);
	free(reserve);
	return (temp);
}

char	*ft_lecteur(int fd, char *reserve)
{
	int		nbr;
	char	*buf;

	if (!reserve)
		reserve = ft_strdup("");
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	nbr = read(fd, buf, BUFFER_SIZE);
	while ((nbr > 0))
	{
		buf[nbr] = '\0';
		reserve = free_join(reserve, buf);
		if (ft_strchr(buf, '\n'))
			break ;
		nbr = read(fd, buf, BUFFER_SIZE);
	}
	if (nbr < 0 || (!nbr && !*reserve))
		return (ft_free(reserve, buf));
	free(buf);
	return (reserve);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*reserve[FILE_D_MAX];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FILE_D_MAX)
		return (NULL);
	reserve[fd] = ft_lecteur(fd, reserve[fd]);
	if (!reserve[fd])
		return (NULL);
	line = ft_cut_line(reserve[fd]);
	reserve[fd] = ft_cut_reste(reserve[fd]);
	if (!reserve[fd])
	{
		free(reserve[fd]);
		reserve[fd] = NULL;
	}
	return (line);
}
