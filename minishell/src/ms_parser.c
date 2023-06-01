/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:18:17 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/01 20:44:23 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mslib.h"

char	*msh_script(const char *s)
{
	char	*sr;
	size_t	len;
	size_t	len2;

	len = ft_strlen(s);
	len2 = 0;
	sr = ft_calloc(sizeof(char), len + 1);
	if (!sr)
		return (0);
	len = 0;
	while (s[len])
	{
		if ((s[len] == '\'' || s[len] == '\"') && s[len - 1] == '\\')
			len2 --;
		else if (s[len] == '\'' || s[len] == '\"')
			len ++;
		sr[len2++] = s[len++];
	}
	sr[len2] = '\0';
	return (sr);
}

char	*msh_strset2(const char *s, int i)
{
	char	*sr;
	size_t	len;
	size_t	len2;

	len = ft_strlen(s);
	len2 = 0;
	sr = ft_calloc(sizeof(char), len + 1);
	if (!sr)
		return (0);
	len = 0;
	while (s[len] && len <= (size_t)i)
		sr[len2++] = s[len++];
	len2 ++;
	sr[len2] = '\0';
	return (sr);
}

char	*msh_strset(const char *s, char c)
{
	char	*sr;
	size_t	len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	sr = ft_calloc(sizeof(char), len + 1);
	if (!sr)
		return (0);
	len = 0;
	while (s[len] != c && s[len])
	{
		sr[len] = s[len];
		len++;
	}
	sr[len] = '\0';
	return (sr);
}

char	*msh_getquotes(const char *s, char c, int qt)
{
	if (qt > 0)
		return (msh_strset2(s, qt));
	else if (qt == -1)
		return (msh_script(s));
	return (msh_strset(s, c));
}
/*
char	**msh_split(char c, t_vars *vars, int quotes, size_t n)
{
	char	**strings;
	size_t	strn;
	int		i;

	i = 0;
	strn = msh_strnum(vars->inpli, c);
	strings = ft_calloc(sizeof(char **), strn + 1);
	if (!strings)
		return (0);
	while (n < strn)
	{
		quotes = msh_check_quotes(vars->inpli[i]);
		if (quotes != 3)
		{
			while (vars->inpli[i] == c || vars->inpli[i] == '\''
				|| vars->inpli[i] == '\"')
				quotes = msh_check_quotes(vars->inpli[i++]);
		}
		strings[n] = msh_getquotes((vars->inpli + i), c, quotes);
		i += ft_strlen(strings[n++]);
	}
	if (vars->inpli != NULL)
		free (vars->inpli);
	return (strings);
}
*/

char	**msh_split(char c, t_vars *vars, size_t n, int i)
{
	int		quote;
	char	**strings;
	size_t	strn;

	strings = msh_setsplit(&quote, &strn, vars, c);
	if (!strings)
		return (0);
	while (n < strn && i < vars->inplen)
	{
		quote = msh_check_quotes(vars, vars->inpli[i], i);
		if (quote != -1)
		{
			while (vars->inpli[i] == c
				|| vars->inpli[i] == '\'' || vars->inpli[i] == '\"')
			{
				quote = msh_check_quotes(vars, vars->inpli[i], i);
				i ++;
			}
		}
		if (i > 0 && (vars->inpli[i - 1] == '\'' || vars->inpli[i - 1] == '\"'))
			i --;
		strings[n] = msh_getquotes((vars->inpli + i), c, quote);
		printf("%zu: %s\n", n, strings[n]);
		i += ft_strlen(strings[n++]);
	}
	return (strings);
}
