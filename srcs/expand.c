/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvandeven <zvandeven@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:54:30 by zvandeven         #+#    #+#             */
/*   Updated: 2023/09/14 18:51:13 by zvandeven        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_cuts(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (str[0] != '$')
		count = 1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			count++;
			i++;
			while (str[i] && (!is_whitespace(str[i]) && str[i] != '$'))
				i++;
			if (!str[i])
				break ;
			count++;
		}
	}
	return (count);
}

void	ft_expand(char **arr)
{
	int	i;
	char	*temp;

	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] == '$')
		{
			if (!is_whitespace(arr[i][1]) && ft_strlen(arr[i]) != 1)
			{	
				temp = getenv(ft_substr(arr[i], 1, ft_strlen(arr[i]) - 1));
				ft_free_str(arr[i]);
				arr[i] = temp;
			}
		}
	}
}

char	*ft_expand_arr(char *str)
{
	char	**arr;
	char	*new_str;
	int 	start;
	int		end;
	int		i;
	int		is_exp;

	i = 0;
	start = 0;
	end = -1;
	is_exp = 0;
	new_str = NULL;
	arr = ft_calloc(ft_count_cuts(str) + 1, sizeof (char *));
	if (!arr)
		ft_putstr_exit("Error: Malloc failed", 2, 1);
	while(i < ft_count_cuts(str))
	{
		while(str[++end])
		{
			if(is_exp == 1 || (end == 0 && str[end] == '$'))
			{
				end++;
				while (str[end] && (!is_whitespace(str[end]) && str[end] != '$'))
					end++;
				is_exp = 0;
				break ;
			}
			if(str[end] == '$')
			{
				is_exp = 1;
				break;
			}
		}
		arr[i] = ft_substr(str, start, end - start);
		start = end;
		i++;
	}
	arr[i] = NULL;
	// ft_printmap(arr);
	ft_expand(arr);
	i = 0;
	while(i < ft_count_cuts(str))
	{
		if (arr[i])
		{
			if (!new_str)
				new_str = arr[i];
			else
				new_str = ft_strjoin(new_str, arr[i]);
		}
		i++;
	}
	// ft_printmap(arr);
	return (new_str);
}

t_tokens	*ft_expand_tokens(t_tokens *tokens)
{
	t_tokens	*ptr;
	char 		*temp;

	ptr = tokens;
	while (tokens != NULL)
	{
		if ((tokens->data->token_id == WORD_EXP
			|| tokens->data->token_id == FLAG_EXP
			|| tokens->data->token_id == D_QUOTE_EXP)
			&& ft_strlen(tokens->data->str) > 1)
		{
			temp = ft_expand_arr(tokens->data->str);
			ft_free_str(tokens->data->str);
			tokens->data->str = temp;
		}
		if (tokens->data->token_id == WORD_EXP)
			tokens->data->token_id = WORD;
		else if (tokens->data->token_id == FLAG_EXP)
			tokens->data->token_id = FLAG;
		else if (tokens->data->token_id == D_QUOTE_EXP)
			tokens->data->token_id = D_QUOTE;
		tokens = tokens->next;
	}
	return (ptr);
}
