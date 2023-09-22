/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:30:15 by oroy              #+#    #+#             */
/*   Updated: 2023/09/22 18:33:24 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_word(char *input, int i)
{
	int	dollar;

	dollar = 0;
	while (input[i])
	{
		if (input[i] == '$')
			dollar = 1;
		if (ft_iswspace(input[i]) || is_meta(input[i]))
			break ;
		i++;
	}
	if (dollar)
		pa()->id = WORD_EXP;
	else
		pa()->id = WORD;
	return (i);
}

int	get_flag(char *input, int i)
{
	int	dollar;

	dollar = 0;
	if (ft_iswspace(input[i + 1]))
	{
		pa()->id = WORD;
		i++;
	}
	else
	{
		while (input[i++])
		{
			if (input[i] == '$')
				dollar = 1;
			if (ft_iswspace(input[i]))
				break ;
		}
		if (dollar)
			pa()->id = FLAG_EXP;
		else
			pa()->id = FLAG;
	}
	return (i);
}

int	meta_specifier(char *input, int i)
{
	if (!input)
		return (0);
	else if (input[i] == '"')
		i = ft_double_quote(input, i);
	else if (input[i] == 39)
		i = ft_single_quote(input, i);
	else if (input[i] == '-')
		i = get_flag(input, i);
	else if (input[i] == '<' || input[i] == '>')
		i = ft_less_great(input, i);
	else if (input[i] == '|')
	{
		i++;
		pa()->id = PIPE;
	}
	return (i);
}

char	*get_string(char *input, int j)
{
	char	*temp;

	if (pa()->id == S_QUOTE || pa()->id == D_QUOTE || pa()->id == D_QUOTE_EXP)
		temp = ft_substr(input, pa()->i + 1, (j - 2) - pa()->i);
	else
		temp = ft_substr(input, pa()->i, j - pa()->i);
	return (temp);
}

t_tokens	*parse_input(char *input)
{
	t_tokens	*tokens;
	char		*temp;
	int			j;

	pa()->i = 0;
	j = 0;
	tokens = NULL;
	while (pa()->i <= ft_strlen_int(input) && input[pa()->i])
	{
		if (ft_iswspace(input[pa()->i]))
			j = get_wspace(input, pa()->i);
		else if (is_meta(input[pa()->i]))
			j = meta_specifier(input, pa()->i);
		else
			j = get_word(input, pa()->i);
		temp = get_string(input, j);
		if (ft_strlen(temp) == 0)
			break ;
		tokens = ft_lstadd_back(tokens,
				ft_lstnew(get_data(temp, pa()->id)));
		pa()->i = j;
	}
	tokens = ft_expand_tokens(tokens);
	tokens = ft_concat_tokens(tokens);
	return (tokens);
}
