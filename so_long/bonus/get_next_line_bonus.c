/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:40:40 by sdiouane          #+#    #+#             */
/*   Updated: 2024/01/28 20:47:23 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*ft_read_line(char *s)
{
	char	*line;
	int		i;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*move_string(char *s)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	i += (s[i] == '\n');
	new = (char *)malloc(ft_strlen(s) - i + 1);
	if (!new)
		return (NULL);
	j = 0;
	while (s[i + j])
	{
		new[j] = s[i + j];
		j++;
	}
	new[j] = '\0';
	free(s);
	return (new);
}

char	*reader(int fd, char *reserve)
{
	int		rd;
	char	*line;

	line = NULL;
	rd = 1;
	line = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	while (!(find(reserve, '\n')) && rd != 0)
	{
		rd = read(fd, line, BUFFER_SIZE);
		if (rd < 0)
		{
			free(line);
			free(reserve);
			return (NULL);
		}
		line[rd] = '\0';
		reserve = ft_strjoin(reserve, line);
	}
	free(line);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	reserve = reader(fd, reserve);
	if (!reserve)
	{
		free(reserve);
		return (NULL);
	}
	line = ft_read_line(reserve);
	reserve = move_string(reserve);
	return (line);
}
