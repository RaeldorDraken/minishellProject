/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:21:49 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/10 22:57:14 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

/**
 * @brief Functions that sets / resets quotes for validation
 * 
 * ? quote -> comillas normales
 * ? miniquote -> comillas simples
 * 
 * @param quote_struct 
 */

void	msh_print_element(char *input, int start, int end)
{
	printf("\nstart es %d y end es %d\n", start, end);

	while (start <= end)
	{
		write(1, &input[start], 1);
		start++;
	}
	printf("\n");
}

void	msh_init_quotes_struct(t_quotes *quote_struct)
{
	quote_struct->quote = 0;
	quote_struct->miniquote = 0;
}

void	msh_update_quotes_status(t_quotes *quotes, char c)
{
	if (c == '"' && quotes->quote == 0 && quotes->miniquote != 1)
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

	c = -0;
	if (str == NULL)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}	
	copy = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!copy)
		return (free_return_null(copy));
	while (str[c])
	{
		copy[c] = str[c];
		c++;
	}
	copy[c] = ch;
	copy[c + 1] = '\0';
	free(str);
	return (copy);
}

char *free_return_null(char *ptr)
{
	free(ptr);
	return (NULL);
}

int	no_quotes(t_quotes *quotes)
{
	if (!quotes->quote && !quotes->miniquote)
		return (1);
	return (0);
}

int	is_startarg(char *input, int c, t_quotes *quotes)
{
	if (c > 0 && input[c] != ' ' && input[c - 1] == ' '
		&& no_quotes(quotes))
		return (1);
	return (0);
}

int	is_endarg(char *input, int c, t_quotes *quotes)
{
	if (input[c] != ' ' && ((input[c + 1] == ' '
				&& no_quotes(quotes)) || input[c + 1] == '\0' ))
		return (1);
	return (0);
}

