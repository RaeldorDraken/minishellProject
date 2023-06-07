/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:21:49 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/07 23:18:48 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ? ft_trim() --> Clean spaces before and after input --> include din lbft
// ? ft_strdup() --> Copy a string and allocate memory. returns allocated memory --> included in libft

#include "../../incl/mslib.h"

// ? ft_strjoin_chr() --> add a char to an allocated string , generating on new, and freeing the old 


void msh_init_quotes_struct(t_quotes *quote_struct)
{
	quote_struct->quote = 0; // ? comillas dobles
	quote_struct->miniquote = 0; // ? comillas simples
}

void msh_update_quotes_status(t_quotes *quotes, char c)
{
		//Evaluar los quotes
		if (c == '"' && quotes->quote == 0 && quotes->miniquote != 1 )
			quotes->quote = 1;
		else if (c == '"' && quotes->quote == 1)
			quotes->quote = 0;
		if (c == '\'' && quotes->miniquote == 0 && quotes->quote != 1)
			quotes->miniquote = 1;
		else if (c == '\'' && quotes->miniquote == 1)
			quotes->miniquote = 0;
}


char	*msh_strjoinchr(char *str, char ch)
{
	char	*copy;
	int		c;

	c = 0;
	if (str == NULL)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';	
	}	
	copy = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!copy)
	{
		free (str);
		return (NULL);
	}	
	while (str[c] != '\0')
	{
		copy[c] = str[c];
		c++;
	}
	copy[c] = ch;
	copy[c + 1] = '\0';
	free(str);
	return (copy);
}

