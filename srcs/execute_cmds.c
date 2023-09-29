/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:39:30 by olivierroy        #+#    #+#             */
/*   Updated: 2023/09/29 19:30:11 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(void)
{
	if (access ("heredoc", F_OK) == 0)
		unlink ("heredoc");
	ft_free_ar(ex()->cmd);
	ft_free_str(ex()->cmdpath);
	ft_clearlst(&ex()->in);
	ft_clearlst(&ex()->out);
	ft_clearlst(&ex()->exec);
}

void	put_redirection(t_tokens *temp, int id)
{
	t_tokens	*ptr;

	temp->data->token_id = id;
	if (id == GREAT || id == GREATGREAT)
	{
		ptr = ft_lstadd_back(ex()->out, temp);
		ex()->out = ptr;
	}
	else
	{
		ptr = ft_lstadd_back(ex()->in, temp);
		ex()->in = ptr;
	}
	ptr = NULL;
}

int	handle_redirections(t_tokens **t)
{
	t_tokens	*new;

	if (!(*t)->next)
		return (exec_error("newline", 258));
	else if ((*t)->next->data->token_id >= 130)
		return (exec_error((*t)->next->data->str, 258));
	else if ((*t)->data->token_id == LESSLESS)
		(*t)->next->data->str = get_heredoc_input((*t)->next->data->str);
	new = ft_lstnew((*t)->next->data);
	if (!new)
		return (exec_error("Malloc error", 1));
	put_redirection(new, (*t)->data->token_id);
	(*t) = (*t)->next;
	return (0);
}

int	add_token(t_tokens **t, t_tokens **temp)
{
	t_tokens	*ptr;
	int			rtn;

	rtn = 0;
	if ((*t)->data->token_id < 129)
	{
		ptr = ft_lstadd_back(ex()->exec, *temp);
		ex()->exec = ptr;
	}
	else
	{
		if ((*t)->data->token_id > 130)
			rtn = handle_redirections(t);
		else if ((*t)->data->token_id == PIPE && (*t)->next)
			parent_process(*t);
		else if ((*t)->data->token_id == PIPE && !(*t)->next)
			rtn = exec_error("|", 258);
		free (*temp);
		*temp = NULL;
	}
	return (rtn);
}

void	execute_cmds(t_tokens *t)
{
	t_tokens	*temp;

	temp = NULL;
	while (t)
	{
		if (!temp && t->data->token_id == PIPE)
		{
			exec_error("|", 258);
			return ;
		}
		temp = ft_lstnew(t->data);
		if (!temp)
		{
			exec_error("Malloc error", 1);
			return ;
		}
		else if (add_token(&t, &temp) > 0)
			return ;
		t = t->next;
	}
	parent_process(t);
	close_tab(ex()->fd);
}
