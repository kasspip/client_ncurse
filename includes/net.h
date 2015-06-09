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

#ifndef NET_H
# define NET_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/socket.h>
# include <stdio.h>
# include <resolv.h>
# include <netdb.h>
# include <stdarg.h>
# include "openssl/ssl.h"
# include "openssl/err.h"

# define BUF_SIZE 4096

typedef struct		s_ssl
{
	SSL				*ssl;
	SSL_CTX			*ctx;
}					t_ssl;

typedef struct		s_net
{
	int				is_connected;
	int				port;
	char			*addr;
	int				sock;
	fd_set			fd_read;
	fd_set			fd_write;
	void			(*ft_read)(struct s_net *);
	void			(*ft_write)(struct s_net *);
	char			buf_read[BUF_SIZE];
	char			buf_write[BUF_SIZE];
	char			**alert;
	t_ssl			ssl;
}					t_net;

void				net_send(t_net *net, char *msg);
int					net_select(t_net *net);
int					net_parse(char *intput, t_net *net);
int					net_connect(t_net *net);
void				net_init(t_net *net);
int					net_close(t_net *net);
void				net_read(t_net *net);
void				net_write(t_net *net);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
char				*stringf(const char *format, ...);

#endif
