/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:21:17 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/17 18:04:12 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_execute_start(t_vars *vars)
{
	//aqui ha de ir todo el desglose para hacer pipes redirecciones y tonterias de multiples comandos

	//probando ejecucion de un comando simple
	write(1 , "enters cmd execute start\n", 26);
	msh_getpath(vars, vars->own_env_vars);
	write(1 , "exits getpath\n", 14);
	msh_cmd_execute(vars);
	return (0); // aqui poner return de error o result cuando toque
}

int	msh_cmd_execute(t_vars *vars)
{
	pid_t	exec_pid;
	char	*temp_cmd;
	
	write(1 , "enters cmd execute\n", 19);
	temp_cmd = msh_getpath_cmd(vars, vars->cmd->argv[0]);
	exec_pid = fork();
	if (exec_pid == 0)
	{
		if (temp_cmd != NULL && vars->cmd->argv[0])
		{
			printf("cmd: %s\n", temp_cmd);
			vars->sigexec = 1;
			execve(temp_cmd, vars->cmd->argv, vars->own_env_vars);
		}
		else
			vars->sigexec = 0;
	}
	else
		waitpid(exec_pid, NULL, 0);
	free(temp_cmd);
	return (vars->sigexec);
}