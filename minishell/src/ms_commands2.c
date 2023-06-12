/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commands2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:33:12 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/12 10:15:06 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/mslib.h"

int	msh_echo_init(t_vars *vars, int i, int *flag)
{
	while (vars->inpcomm[i][0] == '-')
	{
		if (vars->inpcomm[i][1] == 'n')
			*flag = 1;
		else
			break ;
		i++;
	}
	return (i);
}

char	*msh_echo(t_vars *vars, int i, int j, int flag)
{
	char	*echor;

	echor = ft_strdup("");
	i = msh_echo_init(vars, i, &flag);
	while (vars->inpcomm[i])
	{
		j = 0;
		while (j != -1 && vars->tokens[j])
		{
			if (!ft_strcmp(vars->inpcomm[i], vars->tokens[j]))
				j = -1;
			else
				j ++;
		}
		if (j == -1)
		{
			break ;
		}
			echor = ft_joinloc(echor, ft_strdup(vars->inpcomm[i]));
		if (vars->inpcomm[i + 1])
			echor = ft_joinloc(echor, ft_strdup(" "));
		i++;
	}
	if (flag != 1)
		echor = ft_joinloc(echor, ft_strdup("\n"));
	return (echor);
}
