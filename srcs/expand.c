/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvandeven <zvandeven@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:54:30 by zvandeven         #+#    #+#             */
/*   Updated: 2023/09/15 12:07:12 by zvandeven        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_expand(char **arr)
{
	int		i;
	char	*temp;

	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] == '$')
		{
			if (arr[i][1] == '?')
				printf("Do pipe exit status\n");
			else if (!ft_iswspace(arr[i][1]) && ft_strlen(arr[i]) != 1)
			{	
				temp = getenv(ft_substr(arr[i], 1, ft_strlen(arr[i]) - 1));
				ft_free_str(arr[i]);
				arr[i] = temp;
			}
		}
	}
}

void	ft_expand_and_join(char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	ft_expand(x()->arr);
	i = 0;
	while (i < ft_count_cuts(str, '$'))
	{
		if (x()->arr[i])
		{
			if (!tmp)
				tmp = x()->arr[i];
			else
				tmp = ft_strjoin(tmp, x()->arr[i]);
		}
		i++;
	}
	x()->new_str = tmp;
}

void	get_start_and_end(char *str)
{
	while (str[++x()->end])
	{
		if (x()->is_exp == 1 || (x()->end == 0 && str[x()->end] == '$'))
		{
			x()->end++;
			while (str[x()->end]
				&& (!ft_iswspace(str[x()->end]) && str[x()->end] != '$'))
				x()->end++;
			x()->is_exp = 0;
			break ;
		}
		if (str[x()->end] == '$')
		{
			x()->is_exp = 1;
			break ;
		}
	}
}

char	*ft_expand_arr(char *str)
{
	char	**arr;

	arr = ft_calloc(ft_count_cuts(str, '$') + 1, sizeof (char *));
	if (!arr)
		ft_putstr_exit("Error: Malloc failed", 2, 1);
	while (x()->i < ft_count_cuts(str, '$'))
	{
		get_start_and_end(str);
		arr[x()->i] = ft_substr(str, x()->start, x()->end - x()->start);
		x()->start = x()->end;
		x()->i++;
	}
	arr[x()->i] = NULL;
	x()->arr = arr;
	ft_expand_and_join(str);
	return (x()->new_str);
}

t_tokens	*ft_expand_tokens(t_tokens *tokens)
{
	t_tokens	*ptr;

	ptr = tokens;
	while (tokens != NULL)
	{
		if ((tokens->data->token_id >= 102 && tokens->data->token_id <= 104)
			&& ft_strlen(tokens->data->str) > 1)
		{
			x()->temp = ft_expand_arr(tokens->data->str);
			ft_free_str(tokens->data->str);
			if (!x()->temp)
				tokens->data->str = ft_strdup("");
			else
				tokens->data->str = x()->temp;
		}
		if (tokens->data->token_id == WORD_EXP)
			tokens->data->token_id = WORD;
		else if (tokens->data->token_id == FLAG_EXP)
			tokens->data->token_id = FLAG;
		else if (tokens->data->token_id == D_QUOTE_EXP)
			tokens->data->token_id = D_QUOTE;
		x()->init = 0;
		tokens = tokens->next;
	}
	return (ptr);
}
