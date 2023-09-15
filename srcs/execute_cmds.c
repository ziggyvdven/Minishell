/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:39:30 by olivierroy        #+#    #+#             */
/*   Updated: 2023/09/15 12:31:40 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exec	*ex(void)
{
	static t_exec	ex;
	
	return (&ex);
}

void	child_process(void)
{
	get_input();
	get_output();
	dup2_(ex()->fd[0], STDIN_FILENO);
	if (ex()->fd[1])
		dup2_(ex()->fd[1], STDOUT_FILENO);
	else if (!ex()->fd[1] && ex()->pipes[1])
		dup2_(ex()->pipes[1], STDOUT_FILENO);
	close_all();
	get_cmdpath();
	create_cmd_ar();
	execve_(ex()->cmdpath, ex()->cmd, NULL);
}

void	parent_process(t_tokens *token)
{
	pid_t	process_id;
	int		status;

	if (token)
		pipe_(ex()->pipes);
	process_id = fork_();
	if (process_id == 0)
		child_process();
	waitpid_(process_id, &status, 0);
	if (token)
	{
		if (!ex()->fd[0])
			ex()->fd[0] = dup_(ex()->pipes[0]);
		else
			dup2_(ex()->pipes[0], ex()->fd[0]);
		close_tab(ex()->pipes);
	}
	if (access ("heredoc", F_OK) == 0)
		unlink ("heredoc");
	ft_free_ar(ex()->cmd);
	ft_free_str(ex()->cmdpath);
	ft_lstclear(&ex()->in);
	ft_lstclear(&ex()->out);
	ft_lstclear(&ex()->exec);
}

void	put_redirect(t_tokens *temp, int id)
{
	if (!temp)
		ft_putstr_exit("Error: Malloc failed", 2, 1);
	temp->data->token_id = id;
	if (id == GREAT || id == GREATGREAT)
		ex()->out = ft_lstadd_back(ex()->out, temp);
	else
		ex()->in = ft_lstadd_back(ex()->in, temp);
}

char	*add_newline(char *str)
{
	char	*new;
	
	new = ft_strjoin(str, "\n");
	ft_free_str(str);
	return (new);
}

char	*get_heredoc(char *delimiter)
{
	char	*gnl;
	char	*str;
	char	*temp;
	size_t	len;

	str = NULL;
	len = ft_strlen(delimiter);
	ft_putstr_fd("> ", STDIN_FILENO);
	gnl = get_next_line(STDIN_FILENO);
	while (ft_strnstr(gnl, delimiter, len) == NULL)
	{
		if (!str)
			str = ft_strdup(gnl);
		else
		{
			temp = add_newline(str);
			str = ft_strjoin(temp, gnl);
			ft_free_str(temp);
		}
		ft_free_str(gnl);
		ft_putstr_fd("> ", STDIN_FILENO);
		gnl = get_next_line(STDIN_FILENO);
	}
	ft_free_str(gnl);
	return (str);
}

void	execute_cmds(t_tokens *t)
{
	t_tokens	*temp = NULL;

	while (t)
	{
		if (t->data->token_id == PIPE && !temp)
			ft_putstr_exit("syntax error near unexpected token `|'", 2, 1);
		temp = ft_lstnew(t->data);
		if (!temp)
			ft_putstr_exit("Error: Malloc failed", 2, 1);
		if (t->data->token_id < 129)
			ex()->exec = ft_lstadd_back(ex()->exec, temp);
		else if (t->data->token_id > 130 && t->next)
		{
			if (t->data->token_id == LESSLESS)
				t->next->data->str = get_heredoc(t->next->data->str);
			put_redirect(ft_lstnew(t->next->data), t->data->token_id);
			ft_lstdelone(temp);
			t = t->next;
		}
		else if (t->data->token_id == PIPE)
			parent_process(t);
		t = t->next;
	}
	parent_process(t);
	close_tab(ex()->fd);
}
