/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_clearmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:24:24 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/01 11:27:17 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/mslib.h"

void	msh_clearpath(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->paths[i] != NULL)
	{
		free(vars->paths[i]);
		i++;
	}
	free(vars->paths);
}

void	msh_clear_memory(t_vars *vars)
{
	free (vars->prompt);
	if (vars->inpli != NULL)
		free (vars->inpli);
	if (vars->btins != NULL)
		free (vars->btins);
	if (vars->tokens != NULL)
		free (vars->tokens);
	exit(0);
}