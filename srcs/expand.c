/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:54:30 by zvandeven         #+#    #+#             */
/*   Updated: 2023/09/21 13:55:55 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Function expands the token after $

void	ft_expand(char **arr)
{
	int		i;
	char	*temp;
	char	*str;

	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] == '$')
		{
			if (arr[i][1] == '?')
				temp = ft_itoa(ex()->exitcode);
			else if (!ft_iswspace(arr[i][1]) && ft_strlen(arr[i]) != 1)
			{
				str = ft_substr(arr[i], 1, ft_strlen(arr[i]) - 1);
				temp = ft_strdup(getenv(str));
				free (str);
				if (!temp)
					temp = ft_strdup("");
			}
			ft_free_str(arr[i]);
			arr[i] = temp;
		}
	}
}
//Function joins the strings from the array

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
				tmp = ft_strdup(x()->arr[i]);
			else
				tmp = ft_strjoin_free(tmp, x()->arr[i]);
		}
		i++;
	}
	x()->new_str = tmp;
}
//Function that gets the place to cut the string

void	get_start_and_end(char *str)
{
	while (x()->end < ft_strlen_int(str) && str[++x()->end])
	{
		if (x()->is_exp == 1 || (x()->end == 0 && str[x()->end] == '$'))
		{
			x()->end++;
			while (str[x()->end]
				&& (!ft_iswspace(str[x()->end]) && str[x()->end] != '$'
					&& !is_meta(str[x()->end])))
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
//Function that creates an arr with all the cut parts

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
	ft_free_ar(arr);
	return (x()->new_str);
}

t_tokens	*ft_expand_tokens(t_tokens *t)
{
	t_tokens	*ptr;

	ptr = t;
	while (t)
	{
		if ((t->data->token_id >= 102 && t->data->token_id <= 104)
			&& ft_strlen(t->data->str) > 1)
		{
			x()->temp = ft_expand_arr(t->data->str);
			ft_free_str(t->data->str);
			if (!x()->temp)
				t->data->str = ft_strdup("");
			else
				t->data->str = x()->temp;
		}
		if (t->data->token_id == WORD_EXP)
			t->data->token_id = WORD;
		else if (t->data->token_id == FLAG_EXP)
			t->data->token_id = FLAG;
		else if (t->data->token_id == D_QUOTE_EXP)
			t->data->token_id = D_QUOTE;
		x()->init = 0;
		t = t->next;
	}
	return (ptr);
}
