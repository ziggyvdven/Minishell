/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:05:32 by oroy              #+#    #+#             */
/*   Updated: 2023/09/29 13:11:18 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_(int fildes[2])
{
	if (pipe (fildes) == -1)
	{
		perror("Problem with pipe() call");
		close_all();
	}
}

pid_t	fork_(void)
{
	pid_t	process;

	process = fork ();
	if (process == -1)
	{
		perror ("Problem with fork() call");
		close_all();
	}
	return (process);
}

void	execve_(char *path, char **cmd, char **envp)
{
	if (execve (path, cmd, envp) == -1)
	{
		perror ("Problem with execve() call");
	}
}

void	waitpid_(pid_t pid, int *status, int options)
{
	if (waitpid (pid, status, options) == -1)
	{
		perror ("Problem with waitpid() call");
		close_all();
	}
}

void	pars_error_(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	pa()->parse_error = 1;
}

int	exec_error(char *s, int exitcode)
{
	if (exitcode == 127)
	{
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else
	{
		if (exitcode > 1)
			ft_putstr_fd("Parse error near ", 2);
		ft_putendl_fd(s, 2);
	}
	free_cmd();
	ex()->exitcode = exitcode;
	return (exitcode);
}
