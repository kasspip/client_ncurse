#include "ncurses_shell.h"

static void		load_alias(t_map *map_alias)
{
	hash_put(map_alias, "map.size", "msz");
	hash_put(map_alias, "tile.content", "bct");
	hash_put(map_alias, "team.names", "tna");
	hash_put(map_alias, "player.position", "ppo");
	hash_put(map_alias, "player.level", "plv");
	hash_put(map_alias, "player.inventory", "pin");
	hash_put(map_alias, "time.get", "sgt");
	hash_put(map_alias, "time.set", "sst");
}

static void		load_commands(t_map *map_alias)
{
	hash_put(map_alias, "msz", "map.size");
	hash_put(map_alias, "bct", "tile.content");
	hash_put(map_alias, "tna", "team.names");
	hash_put(map_alias, "ppo", "player.position");
	hash_put(map_alias, "plv", "player.level");
	hash_put(map_alias, "pin", "player.inventory");
	hash_put(map_alias, "sgt", "time.get");
	hash_put(map_alias, "sst", "time.set");
}

void			alias_init(t_map *map_alias, t_map *map_cmd)
{
	hash_create_str_str(map_alias, 50);
	hash_create_str_str(map_cmd, 50);
	load_alias(map_alias);
	load_commands(map_cmd);
}