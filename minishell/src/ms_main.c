/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:05:31 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/17 19:03:38 by eros-gir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/mslib.h"

//Global variable
int	msh_store_env_own_vars(t_vars *vars, char **envp)
{
	int	env_length;

	env_length = 0;
	while (envp[env_length])
		env_length++;
	env_length++;
	vars->own_env_vars = (char **)ft_calloc(sizeof(char *), env_length + 1);
	if (!vars->own_env_vars)
		return (0);
	vars->own_env_vars[env_length] = 0;
	env_length = 0;
	while (envp[env_length])
	{
		vars->own_env_vars[env_length] = envp[env_length];
		env_length++;
	}
	vars->own_env_vars[env_length] = NULL;
	return (1);
}

void	msh_sigint_handler(int sig)
{
	if (sig != 0)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	msh_ignore_signals(t_vars *vars, int ac, char **av)
{
	if (ac > 1 || av[1] != NULL)
	{
		printf("ERROR: the program does not take any arguments!");
		exit(1);
	}
	vars->sigbool = 1;
	signal(SIGINT, msh_sigint_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	msh_set_vars(t_vars *vars, char *input, char **envp)
{
	vars->prompt = ft_calloc(ft_strlen(input) + 1, 1);
	vars->inpli = NULL;
	vars->envar = envp;
	vars->sigexec = -1;
	ft_strlcpy(vars->prompt, input, ft_strlen(input));
	msh_acptd_comm(vars);
}

int g_return_status;

int	main(int ac, char **av, char **envp)
{
	t_vars	vars;
	int		looping;

	looping = 1;
	g_return_status = 0;
	msh_ignore_signals(&vars, ac, av);    //Comentar cuando testing
	msh_set_vars(&vars, "msh %  ", envp);	
	msh_store_env_own_vars(&vars, envp); //se necesita para establecer lista de enviroment variables iniciales

	//test own env vars
	/*
	int	i = 0;
	while (vars.own_env_vars[i])
	{
		printf("own_env_vars[%d] = %s\n", i, vars.own_env_vars[i]);
		i ++;
	}
	*/
	
	// for (char **env = envp; *env != 0; env++)
  // {
  //   char *thisEnv = *env;
  //   printf("%s\n", thisEnv);    
  // }

	// ? Capute env vars to hold into own **own_env_vars inside struct s_vars
	//printf("Vars in structure are\n");		
	//if (!msh_store_env_own_vars(vars, envp))
	//	return (-1);	
	//printf("\n");
	// ? End of caputuring env vars

	// Testing mode
	//Test 1: Got to /minishel_tester  and do bash test.sh
	//Test 2: Desde raiz: python3 -m minishell_test
	//https://github.com/thallard/minishell_tester
	//https://github.com/cacharle/minishell_test
/*	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		vars.inpli = av[2];
		vars.inplen = ft_strlen(vars.inpli);
		msh_getting_commands(&vars, envp);
		exit(g_return_status);
	}*/	
	//End testing mode
	while (looping)
	{
		looping = 1;
		vars.inpli = readline(vars.prompt);
		if (vars.inpli != NULL)
		{
			if (vars.inpli[0] == '\0')
			{
				free(vars.inpli);
			}
			add_history(vars.inpli);
			vars.input = msh_sanitize_input(vars.inpli);
			if (vars.input == NULL)
				continue ;
			printf("\ninput sanitized is: |%s|\n", vars.input);
			vars.cmd = msh_tokenize(&vars);
		//	debug_cmd_list(vars.cmd);

		//ejecucion de comandos Primero los built-in, y si no existen pasar al execve con execute
			//? Si el comando es exit, se sale del bucle
			if(ft_strcmp(vars.cmd->argv[0], "exit") == 0)
				looping = 0;

			//? Aqui se ejecuta el comando
			msh_execute_start(&vars);
			
			//msh_split_cmd_argvs(input);

			//vars.inplen = ft_strlen(vars.inpli);
			
			//printf("voy a necesitar %d tokens\n", how_many_tokens_i_need(input));
			// ! Limpiar lista de comandos, con sus argvs, i argv i los tokens de la lista
			// ! free_cmd_list();
			// ! debriamos tambien poner vars.cmd = NULL
		}
		//else
		//	break ;
		//looping = msh_getting_commands(&vars, envp);
		//msh_free_commands(&vars);
		//? free local env vars - I think var structure is freed avobe for anything with a malloc. The following line has no effect using leaks --atExit -- ./minishell
		// free(vars.own_env_vars);
		
}
	//msh_clear_memory(&vars);
}

void debug_cmd_list(t_cmd *first)
{
	t_cmd *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = first;
	while(tmp)
	{
		//debugar token
		printf("Token %d:\n", i);
		printf("argc == %d\n", tmp->argc);
		while(tmp->argv[j])
		{
			printf("argv[%d] = |%s|\n", j, tmp->argv[j]);
			j++;
		}
		printf("is separator = %d\n", tmp->is_separator);
		j = 0;
		i++;
		tmp = tmp->next;
	}
}
