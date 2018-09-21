/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmkwanaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 15:07:06 by lmkwanaz          #+#    #+#             */
/*   Updated: 2018/07/01 12:48:58 by lmkwanaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_saveit(int fd, char **line, char **space)
{
	int		bytes;
	char	*tmp;

	bytes = 0;
	while (space[fd][bytes] != '\n' && space[fd][bytes] != '\0')
		bytes++;
	if (space[fd][bytes] == '\0')
	{
		*line = ft_strdup(space[fd]);
		ft_strdel(&space[fd]);
	}
	else if (space[fd][bytes] == '\n')
	{
		*line = ft_strsub(space[fd], 0, bytes);
		tmp = ft_strdup(&space[fd][bytes + 1]);
		free(space[fd]);
		space[fd] = tmp;
		if (space[fd] == '\0')
			ft_strdel(&space[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*space[1];
	char		buff[BUFF_SIZE + 1];
	int			index;
	char		*tmp;

	if (fd < 0 || !line)
		return (-1);
	while ((index = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[index] = '\0';
		if (space[fd] == NULL)
			space[fd] = ft_strnew(1);
		tmp = ft_strjoin(space[fd], buff);
		free(space[fd]);
		space[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (index < 0)
		return (-1);
	else if (index == 0 && (space[fd] == NULL || space[fd][0] == '\0'))
		return (0);
	return (ft_saveit(fd, line, space));
}
