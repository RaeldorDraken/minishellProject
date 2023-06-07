/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:05:31 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/07 23:09:05 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/mslib.h"

//Global variable

int	msh_store_env_own_vars(t_vars vars, char **envp)
{
	int	env_length;

	env_length = 0;
	while (envp[env_length]) //? get env length
		env_length++;
	vars.own_env_vars = (char **)malloc(sizeof(char *) * env_length + 1);
	if (!vars.own_env_vars)
		return (0);
	
	vars.own_env_vars[env_length] = 0; // ? close array with a null
	env_length = 0;
	// ? Set own env vars into structure
	while (envp[env_length])
	{
		vars.own_env_vars[env_length] = envp[env_length];
		env_length++;
	}
	// ? printing only. Delete on deploy
	env_length = 0;
	while (vars.own_env_vars[env_length])
	{
		printf("\n%d - %s",env_length, vars.own_env_vars[env_length]);
		env_length++;
	}
	//? End of printing
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

//if sigexec == -1 is unset
//if sigexec == 0 is set to error
//if sigexec == 1 is set to success
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
	//End tesyting mode
	
	char *input;
	while (looping)
	{
		looping = 0;
		vars.inpli = readline(vars.prompt);
		if (vars.inpli != NULL)
		{
			if (vars.inpli[0] == '\0')
			{
				free(vars.inpli);
			}
			// validate quotes

			


			input = msh_sanitize_input(vars.inpli);
			printf("input sanitized is: |%s|\n", input);

			//vars.inplen = ft_strlen(vars.inpli);
			
			//printf("voy a necesitar %d tokens\n", how_many_tokens_i_need(input));
			add_history(vars.inpli);
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
