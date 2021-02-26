/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoouali <yoouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:13:45 by yoouali           #+#    #+#             */
/*   Updated: 2021/01/29 09:17:25 by yoouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *tmp)
{
	int		d;
	char	*line;

	d = 0;
	while (tmp[d] != '\n' && tmp[d])
		d++;
	line = malloc(sizeof(char) * (d + 1));
	d = 0;
	while (tmp[d] != '\n' && tmp[d])
	{
		line[d] = tmp[d];
		d++;
	}
	line[d] = '\0';
	return (line);
}

static char	*get_rest(char *tab)
{
	char	*rest;
	char	*endl;

	if (!(endl = ft_strchr(tab, '\n')))
		return (ft_strdup(""));
	rest = ft_strdup(endl + 1);
	return (rest);
}

int			get_next_line(const int fd, char **line)
{
	static char	*tab[FD_N];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			red;

	if (fd < 0 || fd > FD_N || !line || BUFF_SIZE < 1)
		return (-1);
	if (!tab[fd])
		tab[fd] = ft_strnew(1);
	while (!ft_strchr(tab[fd], '\n') && (red = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[red] = '\0';
		tmp = tab[fd];
		tab[fd] = ft_strjoin(tab[fd], buff);
		free(tmp);
	}
	if (red < 1 && !*tab[fd])
		return (red == -1 ? -1 : 0);
	*line = get_line(tab[fd]);
	tmp = tab[fd];
	tab[fd] = get_rest(tab[fd]);
	free(tmp);
	int i = 0;
	return (1);
}
