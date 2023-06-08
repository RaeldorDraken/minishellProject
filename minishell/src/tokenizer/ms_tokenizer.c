/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:30:28 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/08 22:29:02 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

void print_element(char *input, int start, int end)
{
	//"hola que tal"
	//start = 0
	//end = 3

	while (start <= end)
	{
		write(1, &input[start], 1);
		start++;
	}

	printf("\n"); 
}


// start es la posicion 0 o algo que no sea un espacio y que el anterior sea un espacio sin quotes
// end es qe el siguiente caratcer sea un espacio sin quotes o un final de string


// function para segementar el string


// ! Entry point
void	msh_tokenizer(char *input)
{
	int	start;
	int	end;
	int	c;

	c = -1;
	start = 0;
	end = 0;
	while (input[++c])
	{
		if (input[c] && input[c + 1] && input[c] == ' ')
			start = c;
		else if (input[c] && input[c] != ' ')
		{
			if (start != 0)
			{
				print_element(input, start, c);
				// start = 0;
			}
		}
		
	}
}