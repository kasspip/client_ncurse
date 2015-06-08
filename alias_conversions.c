#include "ncurses_shell.h"

static char	*token_not_found(char *token)
{
	if (token)
		free(token);
	return (NULL);
}

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
		return (token_not_found(token));
	free(token);
	if (!args)
		ret = cmd;
	else
	{
		ret = strjoin(cmd, args);
		free(args);
		free(cmd);
	}
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
		return (token_not_found(token));
	free(token);
	if (!args)
		ret = alias;
	else
	{
		ret = strjoin(alias, args);
		free(alias);
		free(args);
	}
	return (ret);
}