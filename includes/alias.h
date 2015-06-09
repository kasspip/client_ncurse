#ifndef ALIAS_H
# define ALIAS_H

#include "hashtable.h"

typedef struct		s_alias
{
	t_map			map_alias;
	t_map			map_cmd;
}					t_alias;

void			alias_init(t_map *map_alias, t_map *map_cmd);
char			*alias_to_cmd(t_map *map_alias, char *input);
char			*cmd_to_alias(t_map *map_cmd, char *input);
void			split_token_args(char *input, char **token, char **args);
char			*strsub(char const *s, unsigned int start, size_t len);

#endif
