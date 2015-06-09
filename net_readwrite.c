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

static void	pad_buffer_read(t_net *net, ssize_t sz)
{
	char	tmp[BUF_SIZE - sz];

	memcpy(tmp, net->buf_read + sz, BUF_SIZE - sz);
	memset(net->buf_read, 0, BUF_SIZE);
	memcpy(net->buf_read, tmp, BUF_SIZE - sz);
	net->len_read -= (sz);
}

static void	pad_buffer_write(t_net *net, ssize_t sz)
{
	char	tmp[BUF_SIZE - sz];

	memcpy(tmp, net->buf_write + sz, BUF_SIZE - sz);
	memset(net->buf_write, 0, BUF_SIZE);
	memcpy(net->buf_write, tmp, BUF_SIZE - sz);
}

void		net_send(t_net *net, char *msg)
{
	strcat(net->buf_write, msg);
	strcat(net->buf_write, "\n");
}

void		net_read(t_net *net)
{
	ssize_t			ret;
	ssize_t			sz;

	ret = SSL_read(net->ssl.ssl, net->buf_read + net->len_read,
		(unsigned)(BUF_SIZE - (net->len_read - 1)));
	if (ret < 0)
		return ;
	net->len_read += ret;
	sz = ret;
	net->server_response = malloc(sizeof(char) * (unsigned)(sz + 1));
	memset(net->server_response, 0, sizeof(char) * (unsigned)(sz + 1));
	strncpy(net->server_response, net->buf_read, sz);
	pad_buffer_read(net, sz);
}

void		net_write(t_net *net)
{
	ssize_t	ret;

	if ((ret = SSL_write(net->ssl.ssl, net->buf_write,
			strlen(net->buf_write))) < 0)
	{
		perror("send:");
		return ;
	}
	pad_buffer_write(net, ret);
}
