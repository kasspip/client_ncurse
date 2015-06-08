#include "ncurses_shell.h"

char	*alias_to_cmd(t_map *map_alias, char *input)
{
	char	*cmd;
	char	*args;
	char	*token;
	char	*ret;

	token = NULL;
	args = NULL;
	ret = NULL;
	split_token_args(input, &token, &args);
	if (!token || !(cmd = hash_get(map_alias, token)))
		return (NULL);
	if (!args)
		ret = cmd;
	else
		ret = strjoin(cmd, args);
	printf("token = |%s| args = |%s| ret = |%s|\n", token, args, ret);
	free(cmd);
	free(token);
	free(args);
	return (ret);
}

char	*cmd_to_alias(t_map *map_cmd, char *input)
{
	char	*alias;
	char	*args;
	char	*token;
	char	*ret;

	token = NULL;
	args = NULL;
	ret = NULL;
	split_token_args(input, &token, &args);
	if (!token || !(alias = hash_get(map_cmd, token)))
		return (NULL);
	if (!args)
		ret = alias;
	else
		ret = strjoin(alias, args);
	free(alias);
	free(args);
	free(token);
	return (ret);
}