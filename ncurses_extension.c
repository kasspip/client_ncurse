/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_extension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobrecht <cobrecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 14:50:37 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/09 13:02:36 by cobrecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

void	line_to_kvp(t_ncurses *nc, char *line)
{
	int	index;

	index = -1;
	while (line[++index])
		if (line[index] == ' ')
			break ;
	if (!index || !line[index])
		return ;
	line[index] = 0;
	init_kvp(nc, line, line + index + 1);
}

int		ncurses_conf_from_file(t_ncurses *nc, char *file)
{
	int		fd;
	char	*line;

	if (!file)
		file = "misc/file.conf";
	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	line = NULL;
	hash_create_str_str((&nc->map), 100);
	while (gnl(fd, &line))
	{
		line_to_kvp(nc, line);
		if (line)
			free(line);
	}
	if (line)
	{
		line_to_kvp(nc, line);
		free(line);
	}
	close(fd);
	return (1);
}
