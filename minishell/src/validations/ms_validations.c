/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_validations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabril-h <rabril-h@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:19:27 by rabril-h          #+#    #+#             */
/*   Updated: 2023/06/08 22:00:25 by rabril-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/mslib.h"

int	msh_chr_can_be_separator(char c)
{
	if (c == '<' || c == '|' || c == '>')
		return (1);
	return (0);
}