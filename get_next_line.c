/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 21:52:56 by aperol-h          #+#    #+#             */
/*   Updated: 2021/08/05 22:37:49 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

void	*line_buffer(int fd, char **line)
{
	char	*buf;
	char	*tmp;
	ssize_t	bytes_read;
	ssize_t	i;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 0;
	i = 0;
	while (!ft_strchr(*line + i, '\n'))
	{
		i += bytes_read;
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		tmp = ft_strjoin(*line, buf);
		free(*line);
		*line = tmp;
	}
	free(buf);
	return (*line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	static char	*leftover = NULL;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (leftover)
		line = leftover;
	else
	{
		line = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	if (!line_buffer(fd, &line) || ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	tmp = ft_strchr(line, '\n');
	leftover = ft_strdup(tmp + 1);
	if (leftover && leftover[0] != '\0' && tmp)
		*++tmp = '\0';
	return (line);
}
