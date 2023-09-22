/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:53:18 by zvandeven         #+#    #+#             */
/*   Updated: 2023/09/22 16:10:54 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_meta(char c)
{
	if (c)
		if (c == '"' || c == '|' || c == '<' || c == '>' || c == 39 || c == '-')
			return (true);
	return (false);
}

int	ft_double_quote(char *input, int i)
{
	int	dollar;

	dollar = 0;
	while (input[i++])
	{
		if (input[i] == '$')
			dollar = 1;
		else if (input[i] == '"')
			break ;
		else if (input[i] == '\0')
			ft_putstr_exit("Double quote\n", 2, 2);
	}
	if (input[i] == '"')
		i++;
	if (dollar)
		pa()->id = D_QUOTE_EXP;
	else
		pa()->id = D_QUOTE;
	return (i);
}

int	ft_single_quote(char *input, int i)
{
	while (input[i++])
	{
		if (input[i] == 39)
			break ;
		else if (input[i] == '\0')
			ft_putstr_exit("single quote\n", 2, 2);
	}
	if (input[i] == 39)
		i++;
	pa()->id = S_QUOTE;
	return (i);
}

int	ft_great(char *input, int i)
{
	if (input[i + 1] == '>')
	{
		pa()->id = GREATGREAT;
		i += 2;
	}
	else
	{
		pa()->id = GREAT;
		i++;
	}
	return (i);
}

int	ft_less(char *input, int i)
{
	if (input[i + 1] == '<')
	{
		pa()->id = LESSLESS;
		i += 2;
	}
	else
	{
		pa()->id = LESS;
		i++;
	}
	return (i);
}
