/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobrecht <cobrecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:02:41 by cobrecht          #+#    #+#             */
/*   Updated: 2015/06/09 14:24:35 by cobrecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"

void			net_init(t_net *net)
{
	bzero(net, sizeof(t_net));
	net->ft_write = net_write;
	net->ft_read = net_read;
}

int				net_close(t_net *net)
{
	SSL_free(net->ssl.ssl);
	close(net->sock);
	SSL_CTX_free(net->ssl.ctx);
	net->is_connected = 0;
	return (1);
}

static int		net_usage(t_net *net)
{
	net->alert = (char**)malloc(sizeof(char*) * 2);
	net->alert[0] = strdup("# Usage: connect <ip> <port(SSL)>");
	net->alert[1] = 0;
	return (0);
}

int				net_parse(char *input, t_net *net)
{
	char	**split;
	char	*port;
	int		i;

	if (strncmp("connect ", input, 8))
		return (0);
	split = ft_strsplit(input, ' ');
	if (!split[1] || !split[2])
		return (net_usage(net));
	net->addr = strdup(split[1]);
	port = strdup(split[2]);
	net->port = atoi(port);
	free(port);
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return (1);
}
