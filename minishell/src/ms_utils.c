/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:06:58 by eros-gir          #+#    #+#             */
/*   Updated: 2023/05/12 11:35:21 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/mslib.h"

char	**msh_setsplit(int *quote, size_t *strn, t_vars *vars, char c)
{
	*quote = 0;
	*strn = msh_strnum(vars->inpli, c);
	return (ft_calloc(sizeof(char **), *(strn) + 1));
}

int	msh_check_quotes(t_vars *vars, char c, int i)
{
	int	oi;

	oi = i;
	while (vars->inpli[++i] != 0)
	{
		if (c == '\'' && vars->inpli[i] == c)
		{
			return (i - oi);
		}
		else if (c == '\"' && vars->inpli[i] == c)
		{
			return (i - oi);
		}
		else if (c == '.')
			return (-1);
	}
	return (0);
}

size_t	msh_strnum(const char *s, char c)
{	
	size_t	len;
	size_t	numb;

	len = 0;
	numb = 0;
	while (s[len])
	{
		while (s[len] && s[len] == c)
			len++;
		numb++;
		while (s[len] && s[len] != c)
		{
			if ((s[len] == '\'' || s[len] == '\"'))
				numb++;
			len++;
		}
	}
	return (numb);
}

size_t	msh_maxvalue(size_t first, size_t second)
{
	if (first > second)
		return (first);
	else
		return (second);
}
