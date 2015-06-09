#include "ncurses_shell.h"

void		nc_print_help(t_ncurses *nc)
{
	nc_add(nc, "#-------COMMANDS------#");
	nc_add(nc, " ");
	nc_add(nc, "#       connect");
	nc_add(nc, "#       map.size");
	nc_add(nc, "#       tile.content");
	nc_add(nc, "#       team.names");
	nc_add(nc, "#       player.position");
	nc_add(nc, "#       player.level");
	nc_add(nc, "#       player.inventory");
	nc_add(nc, "#       time.get ");
	nc_add(nc, "#       time.set ");
	nc_add(nc, " ");
}