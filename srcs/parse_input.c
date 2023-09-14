/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvandeven <zvandeven@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:30:15 by oroy              #+#    #+#             */
/*   Updated: 2023/09/14 18:50:50 by zvandeven        ###   ########.fr       */
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

bool	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

int	ft_double_quote(char *input, int i)
{
	int dollar;

	dollar = 0;
	while (input[i++])
	{
		if (input[i] == '$')
			dollar = 1;
		if (input[i] == '"')
			break ;
	}
	if (input[i] == '\0')
		ft_putstr_exit("Double quote\n", 2, 2);
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
	}
	if (input[i] == '\0')
		ft_putstr_exit("single quote\n", 2, 2);
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

int	get_word(char *input, int i)
{
	int dollar;

	dollar = 0;
	while (input[i])
	{
		if (input[i] == '$')
			dollar = 1;
		if (is_whitespace(input[i]) || is_meta(input[i]))
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
	if (is_whitespace(input[i + 1]))
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
			if (is_whitespace(input[i]))
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
	else if (input[i] == '<')
		i = ft_less(input, i);
	else if (input[i] == '>')
		i = ft_great(input, i);
	else if (input[i] == '|')
	{
		i++;
		pa()->id = PIPE;
	}
	return (i);
}

t_parsing	*pa(void)
{
	static t_parsing	parsing;

	return (&parsing);
}

t_tokens	*parse_input(char *input)
{
	t_tokens	*tokens = NULL;
	char		*temp;

	pa()->i = 0;
	pa()->j = 0;
	while (input[pa()->i])
	{
		while (is_whitespace(input[pa()->i]))
			pa()->i++;
		if (is_meta(input[pa()->i]))
			pa()->j = meta_specifier(input, pa()->i);
		else 
			pa()->j = get_word(input, pa()->i);
		if (pa()->id >= S_QUOTE && pa()->id <= D_QUOTE_EXP)
			temp = ft_substr(input, pa()->i + 1, (pa()->j - 2) - pa()->i);
		else
			temp = ft_substr(input, pa()->i, pa()->j - pa()->i);
		if (ft_strlen(temp) == 0)
			break ;
		tokens = ft_lstadd_back(tokens, ft_lstnew(get_data(temp, pa()->id)));
		pa()->i = pa()->j;
	}
	// ft_printlst(tokens);
	tokens = ft_expand_tokens(tokens);
	return (tokens);
}
