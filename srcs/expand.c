/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:54:30 by zvandeven         #+#    #+#             */
/*   Updated: 2023/10/02 13:38:44 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Function expands the variable after '$' within the token

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
			else if (ft_strlen(arr[i]) == 1)
				temp = ft_strdup("$");
			else if (!ft_iswspace(arr[i][1]) && ft_strlen(arr[i]) != 1)
			{
				str = ft_substr(arr[i], 1, ft_strlen(arr[i]) - 1);
				temp = ft_get_env(str);
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
			if (!tmp)
				pars_error_("Malloc", 2);
		}
		i++;
	}
	x()->new_str = tmp;
}
//Function that gets place to cut the string

int	ft_expand_get_end(char *str, int i)
{
	if (str[i] == '$')
	{
		i++;
		if (str[i] == '$' || str[i] == '?')
			return (i + 1);
		else if (!ft_isalnum(str[i]))
			return (i);
		else
			while (str[i] && ft_isalnum(str[i]))
				i++;
	}
	else
		while (str[i] != '$' && str[i])
			i++;
	return (i);
}
//Function that creates an arr with all the cut parts

char	*ft_expand_arr(char *str)
{
	char	**arr;
	int		end;

	arr = ft_calloc(ft_count_cuts(str, '$') + 1, sizeof (char *));
	if (!arr)
		pa()->parse_error = 1;
	while (x()->i < ft_count_cuts(str, '$'))
	{
		end = ft_expand_get_end(str, x()->start);
		arr[x()->i] = ft_substr(str, x()->start, end - x()->start);
		x()->start = end;
		x()->i++;
	}
	arr[x()->i] = NULL;
	x()->arr = arr;
	ft_expand_and_join(str);
	ft_free_ar(arr);
	return (x()->new_str);
}

// function that checks for '$' and expands the variables

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
