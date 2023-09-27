/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:35:32 by oroy              #+#    #+#             */
/*   Updated: 2023/09/27 16:19:26 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_heredoc(int fd, char *str)
{
	fd = open ("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc");
		close_all();
		exit (EXIT_FAILURE);
	}
	ft_putstr_fd(str, fd);
	close_(fd);
	fd = open ("heredoc", O_RDONLY);
	if (fd == -1)
	{
		perror("heredoc");
		close_all();
		exit (EXIT_FAILURE);
	}
	return (fd);
}

char	*get_heredoc_input(char *delimiter)
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
			temp = str;
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
