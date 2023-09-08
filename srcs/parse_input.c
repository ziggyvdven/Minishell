/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:30:15 by oroy              #+#    #+#             */
/*   Updated: 2023/09/08 13:28:59 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_meta(char c)
{
	if (c)
		if (c == '"' || c == '|' || c == '<' || c == '>' || c == 39 
			|| c == '$')
			return (true);
	return (false);
}

bool	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

// t_tokens	*meta_specifier()

void	parse_input(char *input)
{
	t_tokens	*tokens = NULL;
	char		*temp;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		// if (is_meta(input[i]))
			// tokens = meta_specifier(input[i])
		if (ft_isalpha(input[i]))
		{
			j = i;
			while (input[j] && !is_whitespace(input[j]))
				j++;
			temp = ft_substr(input, i, j - i);
			// printf("%s\n", temp);
			ft_lstadd_back(tokens, ft_lstnew(get_data(temp, WORD)));
			ft_free_str(temp);
			i = j;
		}
		i++;
	}
	ft_printlst(tokens);
}
