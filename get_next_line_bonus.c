/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 21:52:56 by aperol-h          #+#    #+#             */
/*   Updated: 2021/08/05 22:37:34 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

void	*line_buffer(int fd, char **line)
{
	char	*buf;
	char	*tmp;
	ssize_t	i;
	ssize_t	bytes_read;

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

t_fd_leftover	*get_element_for_fd(t_fd_leftover *list, int fd)
{
	t_fd_leftover	*tmp;
	t_fd_leftover	*new;

	tmp = list;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_fd_leftover));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->leftover = NULL;
	new->next = NULL;
	tmp->next = new;
	return (new);
}

void	ft_list_remove_fd(t_fd_leftover *begin_list, int fd)
{
	t_fd_leftover	*tmp;
	t_fd_leftover	*i;

	if (fd == 0)
		return ;
	if (begin_list && begin_list->fd == fd)
	{
		tmp = begin_list;
		begin_list = begin_list->next;
		free(tmp->leftover);
		free(tmp);
	}
	i = begin_list;
	while (i && i->next)
	{
		if (i->next->fd == fd)
		{
			tmp = i->next;
			i->next = tmp->next;
			free(tmp->leftover);
			free(tmp);
			break ;
		}
		i = i->next;
	}
}

char	*init_gnl(t_fd_leftover *leftover_lst, t_fd_leftover **current, int fd)
{
	char	*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	*current = get_element_for_fd(leftover_lst, fd);
	if ((*current)->leftover)
		line = (*current)->leftover;
	else
	{
		line = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char					*line;
	char					*tmp;
	t_fd_leftover			*current;
	static t_fd_leftover	leftover_lst;

	current = NULL;
	line = init_gnl(&leftover_lst, &current, fd);
	if (!line)
		return (NULL);
	if (!line_buffer(fd, &line) || ft_strlen(line) == 0)
	{
		free(line);
		ft_list_remove_fd(&leftover_lst, fd);
		return (NULL);
	}
	tmp = ft_strchr(line, '\n');
	current->leftover = ft_strdup(tmp + 1);
	if (current->leftover && current->leftover[0] != '\0' && tmp)
		*++tmp = '\0';
	if (current && (!current->leftover || current->leftover[0] == '\0'))
		ft_list_remove_fd(&leftover_lst, fd);
	return (line);
}
