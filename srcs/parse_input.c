/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:30:15 by oroy              #+#    #+#             */
/*   Updated: 2023/10/02 13:27:52 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// if no Meta set id to WORD

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

// if Meta is '-' set id to FLAG

int	get_flag(char *input, int i)
{
	if (ft_iswspace(input[i + 1]))
	{
		pa()->id = WORD;
		i++;
	}
	else
	{
		pa()->id = FLAG;
		i++;
	}
	return (i);
}

//Checks if the first character is a meta character

int	meta_specifier(char *input, int i)
{
	if (!input)
		return (0);
	if (ft_iswspace(input[pa()->i]))
		i = get_wspace(input, pa()->i);
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
// Gets the string to put in the token

char	*get_string(char *input, int j)
{
	char	*temp;

	if (is_meta(input[pa()->i]) || ft_iswspace(input[pa()->i]))
		j = meta_specifier(input, pa()->i);
	else
		j = get_word(input, pa()->i);
	if ((pa()->id == S_QUOTE || pa()->id == D_QUOTE) && ft_strlen(input) == 2)
		temp = ft_strdup("");
	else if (pa()->id == S_QUOTE || pa()->id == D_QUOTE
		|| pa()->id == D_QUOTE_EXP)
		temp = ft_substr(input, pa()->i + 1, (j - 2) - pa()->i);
	else
		temp = ft_substr(input, pa()->i, j - pa()->i);
	if (!temp)
		pars_error_("Parse error: Malloc\n", 2);
	if (pa()->parse_error && temp)
	{
		free (temp);
		temp = NULL;
	}
	pa()->j = j;
	return (temp);
}

// Takes the input line and tokenizes it

t_tokens	*parse_input(char *input)
{
	t_tokens	*tokens;
	char		*temp;

	pa()->i = 0;
	pa()->j = 0;
	tokens = NULL;
	while (pa()->i <= ft_strlen_int(input) && input[pa()->i]
		&& pa()->parse_error == 0)
	{
		temp = get_string(input, pa()->j);
		tokens = ft_lstadd_back(tokens,
				ft_lstnew(get_data(temp, pa()->id)));
		pa()->i = pa()->j;
	}
	tokens = ft_expand_tokens(tokens);
	tokens = ft_concat_tokens(tokens);
	return (tokens);
}
