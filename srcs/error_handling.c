/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:05:32 by oroy              #+#    #+#             */
/*   Updated: 2023/10/04 16:00:00 by oroy             ###   ########.fr       */
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
		perror (path);
		exits();
		exit (EXIT_FAILURE);
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
