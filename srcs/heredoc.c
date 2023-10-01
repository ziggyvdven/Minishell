/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:35:32 by oroy              #+#    #+#             */
/*   Updated: 2023/09/30 23:39:53 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_newline(char *old)
{
	char 	*new;

	new = ft_strjoin(old, "\n");
	ft_free_str(old);
	return (new);
}

char	*get_heredoc_input(char *delimiter)
{
	pid_t	process_id;
	int		status;
	char	*gnl;
	char	*str;
	char	*temp;
	size_t	len;
	int		fd;

	str = NULL;
	len = ft_strlen(delimiter);
	process_id = fork_();
	silence_signal();
	if (process_id == 0)
	{
		set_here_sig();
		while (1)
		{
			gnl = readline("> ");
			if (!gnl || ft_strncmp(gnl, delimiter, len) == 0)
			{
				fd = open ("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
				ft_putstr_fd(str, fd);
				ft_free_str(str);
				close_(fd);
				exit (EXIT_SUCCESS);
			}
			if (!str)
				str = ft_strjoin(gnl, "\n");
			else
			{
				temp = ft_strjoin(str, gnl);
				ft_free_str(str);
				str = add_newline(temp);
			}
			ft_free_str(gnl);
		}
	}
	waitpid_(process_id, &status, 0);
	if (WIFEXITED(status))
		ex()->exitcode = WEXITSTATUS(status);
	ft_free_str(delimiter);
	set_signals();
	return (ft_strdup("heredoc"));
}
