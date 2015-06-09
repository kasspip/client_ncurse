/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rda-cost <rda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:58:12 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/01 14:49:49 by rda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "net.h"

void	net_send(t_net *net, char *msg)
{
	if (strlen(msg) >= BUF_SIZE)
		return ;
	memcpy(net->buf_write, msg, strlen(msg));
}

void	net_read(t_net *net)
{
	int		ret;

	bzero(net->buf_read, BUF_SIZE);
	ret = SSL_read(net->ssl.ssl, net->buf_read, sizeof(net->buf_read));
}

void	net_write(t_net *net)
{
	SSL_write(net->ssl.ssl, net->buf_write, strlen(net->buf_write));
	bzero(net->buf_write, BUF_SIZE);
}
