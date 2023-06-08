/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:07:56 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/08 22:00:57 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"


//Cuantos separadores hay
// << < >> > |
// hola "que tal '" ''' como estas  -> 1
// hola que tal "|" como estas -> 1
// hola que tal '"|"' como estas -> 1
// hola que tal << como estas -> 3
// <<<<< -> 3
// << << < -> 3

//hola    que tal "'      "      "' "  

/**
 * @brief function para usar despues de sanitaze_input
 * 
 * @param input 
 * @return int 
 */


// int how_many_tokens_i_need(char *input)
// {
// 	int quote; // ? comillas dobles
// 	int miniquote;// ? comillas simples
// 	int tokens; // ? numero de tokens

// 	quote = 0;
// 	miniquote = 0;
// 	tokens = 0;
// 	while (*input)
// 	{
// 		//Evaluar los quotes
// 		if (*input == '"' && quote == 0 && miniquote != 1 )
// 			quote = 1;
// 		else if (*input == '"' && quote == 1)
// 			quote = 0;
// 		if (*input == '\'' && miniquote == 0 && quote != 1)
// 			miniquote = 1;
// 		else if (*input == '\'' && miniquote == 1)
// 			miniquote = 0;

// 		//....  
// 		if (chr_can_be_separator(*input))
// 		{
// 			if (*input == '<' && *(input + 1) == '<')
// 			{
// 				tokens++;
// 				input++;
// 			}
// 			else if (*input == '>' && *(input + 1) == '>')
// 			{
// 				tokens++;
// 				input++;
// 			}else
// 			{
// 				tokens++;
// 			}
// 			//if (*(input + 1) + 1)
// 		}
// 	}

// 	return (tokens);
// }



char	*msh_clean_irrelveant_spaces_in_input(char *input)
{
	char		*new_input;
	t_quotes	quotes;
	size_t		c;

	msh_init_quotes_struct(&quotes);
	new_input = NULL;
	c = -1;
	while (input[++c])
	{
		msh_update_quotes_status(&quotes, input[c]);
		if (input[c] != ' ')
			new_input = msh_strjoinchr(new_input, input[c]);
		else if (input[c] == ' ' && (quotes.quote == 1
				|| quotes.miniquote == 1))
			new_input = msh_strjoinchr(new_input, input[c]);
		else if (input[c] == ' ' && (quotes.quote == 0
				|| quotes.miniquote == 0))
		{
			new_input = msh_strjoinchr(new_input, input[c]);
			while (input[c] == ' ' && input[c + 1] == ' ')
				c++;
		}
	}
	free(input);
	return (new_input);
}

int	msh_malformed_quotes(char *input)
{
	int			c;
	t_quotes	quotes;

	c = -1;
	msh_init_quotes_struct(&quotes);
	while (input[++c])
		msh_update_quotes_status(&quotes, input[c]);
	if (quotes.quote == 1 || quotes.miniquote == 1){
		write(2, "Malformed input. Please close your quotes\n", 42);
		return (1);
	}
	return (0);
}

// ! Entry point
char	*msh_sanitize_input(char *input)
{
	printf("input UNsanitized is: |%s|\n\n", input);
	if (msh_malformed_quotes(input))
		return (NULL);
	input = ft_strtrim(input, " ");
	input = msh_clean_irrelveant_spaces_in_input(input);
	return (input);
}



