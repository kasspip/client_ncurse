/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobrecht <cobrecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 10:57:12 by cobrecht          #+#    #+#             */
/*   Updated: 2015/06/09 14:41:14 by cobrecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncurses_shell.h"

static char	*arg_to_str(va_list *arg, char c)
{
	if (c == 's')
		return (strdup(va_arg(*arg, char*)));
	else if (c == 'd')
		return (ft_itoa(va_arg(*arg, int)));
	else
		return (NULL);
}

static char *join_string(char **str1, char **str2)
{
	char	*ret;

	if (*str1 && *str2)
		ret = strjoin(*str1, *str2);
	else
		ret = strdup(*str2);
	if (*str1)
		free(*str1);
	if (*str2)
		free(*str2);
	return (ret);
}

static int	norme_made_me_do_it(int *i, int *start)
{
	*i += 1;
	*start = *i + 1;
	return (0);
}

static char	*concat_msg(const char *format, va_list *arg, int i, int start)
{
	size_t	len;
	char	*string;
	char	*add;

	len = 0;
	string = NULL;
	add = NULL;
	while (format[++i])
	{
		len++;
		if (format[i] == '%')
		{
			add = strsub(format, start, len - 1);
			string = join_string(&string, &add);
			add = arg_to_str(arg, format[i + 1]);
			string = join_string(&string, &add);
			len = norme_made_me_do_it(&i, &start);
		}
		else if (format[i + 1] == '\0')
		{
			add = strsub(format, start, len);
			string = join_string(&string, &add);
		}
	}
	return (string);
}

char		*stringf(const char *format, ...)
{
	va_list	arg;
	char	*msg;
	int		i;
	int		start;

	i = -1;
	start = 0;
	msg = NULL;
	va_start(arg, format);
	msg = concat_msg(format, &arg, i, start);
	va_end(arg);
	return (msg);
}
