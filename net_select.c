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

static void		set_fd(t_net *net)
{
	FD_ZERO(&net->fd_read);
	FD_ZERO(&net->fd_write);
	FD_SET(net->sock, &net->fd_read);
	if (strlen(net->buf_write))
		FD_SET(net->sock, &net->fd_write);
}

static void		select_fd(t_net *net)
{
	struct timeval	timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	select(net->sock + 1, &net->fd_read,
		&net->fd_write, NULL, &timeout);
}

static void		check_fd(t_net *net)
{
	if (FD_ISSET(net->sock, &net->fd_write))
		net->ft_write(net);
	if (FD_ISSET(net->sock, &net->fd_read))
		net->ft_read(net);
}

int				net_select(t_net *net)
{
	set_fd(net);
	select_fd(net);
	check_fd(net);
	return (1);
}
