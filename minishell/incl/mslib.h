/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mslib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:06:39 by eros-gir          #+#    #+#             */
/*   Updated: 2023/06/08 21:59:58 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSLIB_H
# define MSLIB_H

# include<stdio.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<fcntl.h>
# include<sys/wait.h>
# include<sys/stat.h>
# include<sys/ioctl.h>
# include<signal.h>
# include<dirent.h>
# include<termios.h>
# include<curses.h>
# include<term.h>

# include"../libft/libft.h"

typedef struct s_quotes {
	int	quote;
	int	miniquote;
}	t_quotes;

typedef struct s_separator {
	int		index;
	char	*separator;
	char	*prev_token;
	char	*next_token;
}	t_separator;

typedef struct s_cmd {
	int				index;
	char			*cmd;
	int				is_separator;
	struct s_cmd	*next;	
}	t_cmd;

typedef struct s_vars
{
	char	**own_env_vars;
	char	*prompt;
	char	*inpli;
	char	**inpcomm;
	char	**btins;
	char	**tokens;
	char	**envar;
	int		inplen;
	int		sigbool;
	int		sigexec;
	char	**paths;
	char	**cmd_buffer;
	t_cmd	*cmd;
}	t_vars;

size_t	msh_maxvalue(size_t first, size_t second);
size_t	msh_strnum(const char *s, char c);

int		msh_check_quotes(t_vars *vars, char c, int i);
int		msh_getting_commands(t_vars *vars, char **envp);
int		msh_getting_envp_commands(t_vars *vars, char **envp);
int		msh_cmd_execute(t_vars *vars, char **envp, char *cmd);

char	**msh_split(char c, t_vars *vars, size_t n, int i);
char	**msh_setsplit(int *quote, size_t *strn, t_vars *vars, char c);
char	**msh_get_cmds(t_vars *vars, int i);

char	*msh_echo(t_vars *vars, int i, int j, int flag);
char	*msh_getpath_cmd(t_vars *vars, char *cmd);
char	*msh_getpath_line(char **envp);

void	msh_acptd_comm(t_vars *vars);
void	msh_free_commands(t_vars *vars);
void	msh_clear_memory(t_vars *vars);
void	msh_clearpath(t_vars *vars);
void	msh_getpath(t_vars *vars, char **envp);

int		how_many_tokens_i_need(char *input);
// Utils
char	*msh_sanitize_input(char *str);
char	*msh_strjoinchr(char *str, char ch);
void	msh_update_quotes_status(t_quotes *quotes, char c);
void	msh_init_quotes_struct(t_quotes *quote_struct);
// Validators
int		msh_chr_can_be_separator(char c);

// Tokenizer
void	msh_tokenizer(char *input);

#endif