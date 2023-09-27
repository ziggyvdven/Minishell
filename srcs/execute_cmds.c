/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:39:30 by olivierroy        #+#    #+#             */
/*   Updated: 2023/09/26 19:44:33 by oroy             ###   ########.fr       */
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

void	fork_process(void)
{
	pid_t	process_id;
	int		status;

	process_id = fork_();
	if (process_id == 0)
	{
		close_all();
		get_cmdpath();
		create_cmd_ar();
		execve_(ex()->cmdpath, ex()->cmd, NULL);
		exit (EXIT_SUCCESS);
	}
	waitpid_(process_id, &status, 0);
	if (WIFEXITED(status))
		ex()->exitcode = WEXITSTATUS(status);
}

void	parent_process(t_tokens *token)
{
	if (token)
		pipe_(ex()->pipes);
	get_input();
	get_output();
	ex()->saves[0] = dup_(STDIN_FILENO);
	ex()->saves[1] = dup_(STDOUT_FILENO);
	dup2_(ex()->fd[0], STDIN_FILENO);
	if (ex()->fd[1])
		dup2_(ex()->fd[1], STDOUT_FILENO);
	else if (!ex()->fd[1] && ex()->pipes[1])
		dup2_(ex()->pipes[1], STDOUT_FILENO);
	if (!is_builtin(ex()->exec->data->str))
		fork_process();
	close_tab(ex()->fd);
	if (token)
	{
		ex()->fd[0] = dup_(ex()->pipes[0]);
		close_tab(ex()->pipes);
	}
	dup2_(ex()->saves[0], STDIN_FILENO);
	dup2_(ex()->saves[1], STDOUT_FILENO);
	close_tab(ex()->saves);
	free_cmd();
}

void	put_redirection(t_tokens *temp, int id)
{
	t_tokens	*ptr;

	if (!temp)
		ft_putstr_exit("Error: Malloc failed", 2, 1);
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

void	execute_cmds(t_tokens *t)
{
	t_tokens	*temp;
	t_tokens	*ptr;

	temp = NULL;
	while (t)
	{
		if (!temp && t->data->token_id == PIPE)
			ft_putstr_exit("syntax error near unexpected token `|'", 2, 1);
		temp = ft_lstnew(t->data);
		if (!temp)
			ft_putstr_exit("Error: Malloc failed", 2, 1);
		if (t->data->token_id < 129)
		{
			ptr = ft_lstadd_back(ex()->exec, temp);
			ex()->exec = ptr;
		}
		else if (t->data->token_id > 130)
		{
			if (!t->next)
			{
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putstr_fd(t->data->str, 2);
				ft_putstr_exit("'\n", 2, 1);
			}
			else if (t->data->token_id == LESSLESS)
				t->next->data->str = get_heredoc_input(t->next->data->str);
			put_redirection(ft_lstnew(t->next->data), t->data->token_id);
			ft_lstdelone(temp);
			t = t->next;
		}
		else if (t->data->token_id == PIPE && t->next)
			parent_process(t);
		t = t->next;
	}
	parent_process(t);
	close_tab(ex()->fd);
}
