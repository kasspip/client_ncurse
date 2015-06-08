/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:50:28 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/03 15:12:07 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

#include <fcntl.h>
#include <unistd.h>

#define LOG "log.txt"
#define MOD  S_IRUSR | S_IWUSR |S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

void			net_receive(t_ncurses *nc, t_net *net)
{
	net_select(net);
	if (net->buf_read[0])
	{
		nc_add(nc, net->buf_read);
		bzero(net->buf_read, BUF_SIZE);
	}
}

void			net_alert(t_ncurses *nc, t_net *net)
{
	int			i;

	if (net->alert)
	{
		i = -1;
		while (net->alert[++i])
			nc_add(nc, net->alert[i]);
		i = -1;
		while (net->alert[++i])
			free(net->alert[i]);
		free(net->alert);
		net->alert = NULL;
	}
}

void	log_txt(char *lg)
{
	int				fd;
	const mode_t	mode = MOD;

	fd = open(LOG, O_RDWR | O_CREAT | O_APPEND, mode);
	write(fd, lg, strlen(lg));
	write(fd, "\n", 1);
	close(fd);
}

/*
**	nc_start open a new ncurses window
**	nc_loop handles input, history, and line-edition
**	(char *) nc.input is freed at each start of loop
**	you have to duplicate it if you want keep it in memory
**	To add something in the shell, use nc_add
**	nc_end only calls endwin()
*/

int		main(int argc, char **argv)
{
	t_ncurses	nc;
	t_net		client;
	t_alias		alias;
	char		*zappy_cmd;

	/*
	**	argv[1] will add entries in radix_tree for auto completion
	*/

	if (!nc_start(&nc, argc, argv))
		return (nc_delete(&nc));
	net_init(&client);
	alias_init(&(alias.map_alias), &(alias.map_cmd));
	while (!nc.stopped)
	{
		nc_loop(&nc);
		if (nc.input != NULL)
		{
			if (!client.is_connected && net_parse(nc.input, &client))
				 net_connect(&client);
			else
				net_send(&client, nc.input);
			if ((zappy_cmd = alias_to_cmd(&(alias.map_alias), nc.input)))
			{
				log_txt(zappy_cmd);
				nc_add(&nc, zappy_cmd);
			}
			else
			{
				log_txt(nc.input);
				nc_add(&nc, nc.input);
			}
		}
		net_alert(&nc, &client);
		if (client.is_connected)
			net_receive(&nc, &client);
	}
	if (client.is_connected)
		net_close(&client);
	return (nc_delete(&nc));
}
