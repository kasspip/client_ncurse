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

#ifndef ALIAS_H
# define ALIAS_H

# include "hashtable.h"

typedef struct	s_alias
{
	t_map		map_alias;
	t_map		map_cmd;
}				t_alias;

void			alias_init(t_map *map_alias, t_map *map_cmd);
char			*alias_to_cmd(t_map *map_alias, char *input);
char			*cmd_to_alias(t_map *map_cmd, char *input);
void			split_token_args(char *input, char **token, char **args);
char			*strsub(char const *s, unsigned int start, size_t len);

#endif
