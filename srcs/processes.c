/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:37:08 by oroy              #+#    #+#             */
/*   Updated: 2023/10/06 12:12:27 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(void)
{
	pid_t	process_id;
	int		status;

	silence_signal();
	process_id = fork_();
	if (process_id == 0)
	{
		set_here_sig();
		close_all();
		get_cmdpath();
		create_cmd_ar();
		create_env_ar();
		execve_(ex()->cmdpath, ex()->cmd, t()->env_arr);
	}
	waitpid_(process_id, &status, 0);
	if (WIFEXITED(status))
		ex()->exitcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ex()->exitcode = 130;
	set_signals();
}

void	parent_process(t_tokens *token)
{
	if (token)
		pipe_(ex()->pipes);
	if (!get_input() || !get_output())
		return ;
	ex()->saves[0] = dup_(STDIN_FILENO);
	ex()->saves[1] = dup_(STDOUT_FILENO);
	dup2_(ex()->fd[0], STDIN_FILENO);
	if (ex()->fd[1])
		dup2_(ex()->fd[1], STDOUT_FILENO);
	else if (!ex()->fd[1] && ex()->pipes[1])
		dup2_(ex()->pipes[1], STDOUT_FILENO);
	if (ex()->exec && !is_builtin(ex()->exec->data->str))
		child_process();
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
