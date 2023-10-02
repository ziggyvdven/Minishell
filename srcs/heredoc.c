/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:35:32 by oroy              #+#    #+#             */
/*   Updated: 2023/10/02 14:00:12 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_exit(char *str)
{
	int	fd;

	fd = open ("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror ("heredoc");
		ft_free_str(str);
		exit (EXIT_FAILURE);
	}
	ft_putstr_fd(str, fd);
	ft_free_str(str);
	close_(fd);
	exit (EXIT_SUCCESS);
}

void	heredoc_child(size_t len, char *delimiter)
{
	char	*gnl;
	char	*str;
	char	*temp;

	str = NULL;
	while (1)
	{
		gnl = readline("> ");
		if (!gnl || ft_strncmp(gnl, delimiter, len) == 0)
		{
			ft_free_str(gnl);
			heredoc_exit(str);
		}
		if (!str)
			str = ft_strjoin(gnl, "\n");
		else
		{
			temp = ft_strjoin(str, gnl);
			ft_free_str(str);
			str = ft_strjoin(temp, "\n");
			ft_free_str(temp);
		}
		ft_free_str(gnl);
	}
}

char	*get_heredoc_input(char *delimiter)
{
	pid_t	process_id;
	int		status;
	size_t	len;

	len = ft_strlen(delimiter);
	silence_signal();
	process_id = fork_();
	if (process_id == 0)
	{
		set_here_sig();
		heredoc_child(len, delimiter);
	}
	waitpid_(process_id, &status, 0);
	if (WIFEXITED(status))
		ex()->exitcode = WEXITSTATUS(status);
	ft_free_str(delimiter);
	set_signals();
	return (ft_strdup("heredoc"));
}
