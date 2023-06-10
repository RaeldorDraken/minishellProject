/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:30:28 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/10 19:37:05 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"



char **msh_prepare_splitted_input_in_cmds(char *input)
{
	char **splitted;
	int c;
	int num;
	int start;
	char *cmd;
	t_quotes	quotes;
	c = 0;
	num = 0;
	start = 0;
		msh_init_quotes_struct(&quotes);
	splitted = malloc(sizeof(char *) * (msh_how_many_tokens_i_need(input) + 1));
	while (input[c])
	{
		msh_update_quotes_status(&quotes, input[c]);
		
		if(msh_chr_can_be_separator(input[c]) && !quotes.quote && !quotes.miniquote)
		{
			if(ft_strlen(cmd))
			{
				splitted[num] = cmd;
				cmd = NULL;
				num++;
			}

			if(input[c] == '<' && input[c + 1] == '<')
			{
				cmd = msh_strjoinchr(cmd, input[c]);
				cmd = msh_strjoinchr(cmd, input[c]);
				c++;
				splitted[num] = cmd;
				cmd = NULL;
				num++;
			}
			else if(input[c] == '>' && input[c + 1] == '>')
			{
				cmd = msh_strjoinchr(cmd, input[c]);
				cmd = msh_strjoinchr(cmd, input[c]);
				c++;
				splitted[num] = cmd;
				cmd = NULL;
				num++;
			}
			else
			{
				cmd = msh_strjoinchr(cmd, input[c]);
				splitted[num] = cmd;
				cmd = NULL;
				num++;
			}
		}
		else
		{
			cmd = msh_strjoinchr(cmd, input[c]);
		}
		c++;
	}
	if(cmd != NULL)
	{
		splitted[num++] = cmd;
	}
	splitted[num] = NULL;
	return splitted;
}


//msh_split_cmd_argvs
t_cmd *create_token(char *input)
{

	t_cmd *new = malloc(sizeof(t_cmd) * 1);
	//Deveriamos contar numero de argv i setear argc
	new->argc = msh_how_many_argv_have_the_cmd(input);
	new->argv = msh_split_cmd_argvs(input, new->argc);
	new->is_separator = msh_chr_can_be_separator(new->argv[0][0]);
	//hacer malloc para la matriz argv
	//copiar los argv
	//poner si es de tipo seprador o no
	return(new);
}

t_cmd *msh_tokenize(char *input)
{
	t_cmd *my_cmd_list;
	t_cmd *new;
	t_cmd *last;
	int c;

	c = 0;
	my_cmd_list = NULL;
	char **splitted_cmds;
	splitted_cmds = msh_prepare_splitted_input_in_cmds(input);
	while(splitted_cmds[c])
	{
		printf("cmd[%d]: %s\n", c, splitted_cmds[c]);
		new = create_token(splitted_cmds[c]);
		if(!my_cmd_list){
			my_cmd_list = new;
			last = new;
		}
		else
		{
			last->next = new;
			last = new;
		}
		last->next = NULL;
		c++;
	}
	return (my_cmd_list);
}

/**
 * @brief function para segementar el string
 * 
 * @param input 
 * @return int 
 */


int msh_how_many_tokens_i_need(char *input)
{
	
	int tokens; // ? numero de tokens

	t_quotes	quotes;
	int c;
	
	c = 0;
	tokens = 0;
	msh_init_quotes_struct(&quotes);
	while (input[c])
	{
		
		msh_update_quotes_status(&quotes, input[c]);
		if(!msh_chr_can_be_separator(input[c]))
		{
			tokens++;
			while(input[c] && (!msh_chr_can_be_separator(input[c]) || (msh_chr_can_be_separator(input[c]) && (quotes.quote || quotes.miniquote))))
			{
				c++;
				msh_update_quotes_status(&quotes, input[c]);
			}
		}
		if (msh_chr_can_be_separator(input[c]) && !quotes.quote && !quotes.miniquote)
		{
			if (input[c] == '<' && input[c + 1] == '<')
			{
				tokens++;
				c++;
			}
			else if (input[c] == '>' && input[c + 1] == '>')
			{
				tokens++;
				c++;
			}
			else
			{
				tokens++;
			}
		}
		c++;
		if(input[c] == ' ' && !quotes.quote && !quotes.miniquote)
			c++;
	}
	printf("I detected %d needed tokens for this input\n", tokens);
	return (tokens);
}






// ! Entry point
// Esto me puede servir para generar los argv de cada token
char **msh_split_cmd_argvs(char *input, int argc)
{
	t_quotes	quotes;
	int			start;
	int			c;
	int num;
	char **result;
	c = -1;
	start = 0;
	num = 0;
	result = malloc(sizeof(char *) * (argc + 1));
	msh_init_quotes_struct(&quotes);
	while (input[++c])
	{

		if (c == 0 && !quotes.quote && !quotes.miniquote)
			start = c;
		if (c > 0 && input[c] != ' '
			&& input[c - 1] == ' ' && !quotes.quote && !quotes.miniquote)
			start = c;
		msh_update_quotes_status(&quotes, input[c]);
		if (input[c] != ' ' && ((input[c + 1] == ' '
					&& !quotes.quote && !quotes.miniquote)
				|| input[c + 1] == '\0' ))
		{
					//msh_print_element(input, start, end);
					result[num] = ft_substr(input, start, c - start + 1);
					num++;
		}
			
	}

		result[num] = NULL;
		return(result);			

	// printf("\nEl numero de tokens que necesito es --> %d", how_many_tokens_i_need(input));
}

int	msh_how_many_argv_have_the_cmd(char *input)
{
	t_quotes	quotes;
	int			num;
	int			end;
	int			c;

	c = -1;
	num = 0;
	end = 0;
	msh_init_quotes_struct(&quotes);
	while (input[++c])
	{
		msh_update_quotes_status(&quotes, input[c]);
		if (input[c] != ' ' && ((input[c + 1] == ' '
					&& !quotes.quote && !quotes.miniquote)
				|| input[c + 1] == '\0' ))
		{
					num++;
		}
							
	}
printf("For this token num argvs are %d\n", num);
return(num);

	// printf("\nEl numero de tokens que necesito es --> %d", how_many_tokens_i_need(input));
}		

//  hola "que tal " como estas | echo hola  a << b  

// if (input[c + 1] == '\0'
// 			|| (input[c] != ' ' && input[c + 1] == ' '
// 				&& quotes.quote == 0 && quotes.miniquote == 0))

// if ((input[c] != ' ' && input[c + 1] == ' ')
// 			|| (input[c + 1] == '\0'
// 				&& quotes.quote == 0 && quotes.miniquote == 0))



