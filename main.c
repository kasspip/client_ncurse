/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobrecht <cobrecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:50:28 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/09 14:38:19 by cobrecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

#include <fcntl.h>
#include <unistd.h>

#define LOG "log.txt"
#define MOD  S_IRUSR | S_IWUSR |S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

static void		log_txt(char *lg)
{
	int				fd;
	const mode_t	mode = MOD;

	fd = open(LOG, O_RDWR | O_CREAT | O_APPEND, mode);
	write(fd, lg, strlen(lg));
	write(fd, "\n", 1);
	close(fd);
}

static void		net_receive(t_ncurses *nc, t_net *net)
{
	char	*server_response;

	server_response = NULL;
	net_select(net);
	if (net->buf_read[0])
	{
		server_response = stringf("server > %s", net->buf_read);
		bzero(net->buf_read, BUF_SIZE);
		nc_add(nc, server_response);
		log_txt(server_response);
		free(server_response);
	}
}

static void		net_alert(t_ncurses *nc, t_net *net)
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

static void		input_manager(t_ncurses *nc, t_net *client, t_alias *alias)
{
	char		*zappy_cmd;

	if (!client->is_connected && net_parse(nc->input, client))
		net_connect(client);
	else if (!strcmp(nc->input, "help"))
		nc_print_help(nc);
	else
	{
		if ((zappy_cmd = alias_to_cmd(&(alias->map_alias), nc->input)))
		{
			log_txt(zappy_cmd);
			net_send(client, zappy_cmd);
		}
		else
		{
			log_txt(nc->input);
			net_send(client, nc->input);
		}
	}
}

int				main(int argc, char **argv)
{
	t_ncurses	nc;
	t_net		client;
	t_alias		alias;

	(void)argc;
	if (!nc_start(&nc, argv))
		return (nc_delete(&nc));
	net_init(&client);
	alias_init(&(alias.map_alias), &(alias.map_cmd));
	while (!nc.stopped)
	{
		nc_loop(&nc);
		if (nc.input != NULL)
			input_manager(&nc, &client, &alias);
		net_alert(&nc, &client);
		if (client.is_connected)
			net_receive(&nc, &client);
	}
	if (client.is_connected)
		net_close(&client);
	return (nc_delete(&nc));
}
