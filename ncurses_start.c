/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobrecht <cobrecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:53:17 by rda-cost          #+#    #+#             */
/*   Updated: 2015/06/09 13:47:21 by cobrecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static void		welcome(t_ncurses *nc, int autocompletion)
{
	nc_add(nc, "# Welcome to SSL zappy client.");
	nc_add(nc, "# Type 'help' for commands list.");
	if (autocompletion)
		nc_add(nc, "# Press TAB key to auto-complete commands.");
	else
		nc_add(nc, "# Auto-completion off. Could not load a config file.");
	nc_add(nc, "# Press ESC to quit.");
	nc_add(nc, " ");
	nc_add(nc, "# Please connect to server.");
	nc_add(nc, " ");
}

static void		init_fcts(t_ncurses *nc)
{
	nc_fct_init(&(nc->fcts[0]), KEY_LEFT, nc_left);
	nc_fct_init(&(nc->fcts[1]), KEY_RIGHT, nc_right);
	nc_fct_init(&(nc->fcts[2]), '\n', nc_enter);
	nc_fct_init(&(nc->fcts[3]), DEL_K, nc_del);
	nc_fct_init(&(nc->fcts[4]), KEY_UP, nc_up);
	nc_fct_init(&(nc->fcts[5]), KEY_DOWN, nc_down);
	nc_fct_init(&(nc->fcts[6]), '\t', nc_tab);
}

void			init_kvp(t_ncurses *nc, char *k, char *v)
{
	radix_insert(&(nc->search.tree), k);
	hash_put(&(nc->map), k, v);
}

static int		nc_init_radix(t_ncurses *nc, char **av)
{
	memset(&(nc->search), 0, sizeof(t_search));
	if (!ncurses_conf_from_file(nc, av[1]))
	{
		hash_create_str_str((&nc->map), 100);
		return (0);
	}
	return (1);
}

bool			nc_start(t_ncurses *nc, char **av)
{
	int			autocompletion;

	memset(nc, 0, sizeof(t_ncurses));
	memset(&(nc->str), 0, sizeof(t_str));
	autocompletion = nc_init_radix(nc, av);
	if (!(nc->win = initscr()))
		return (false);
	noecho();
	keypad(nc->win, TRUE);
	cbreak();
	nodelay(nc->win, TRUE);
	getmaxyx(nc->win, nc->sz.y, nc->sz.x);
	nc->stopped = false;
	init_fcts(nc);
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	nc_display(nc);
	welcome(nc, autocompletion);
	return (true);
}
