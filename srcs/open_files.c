/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:41:55 by olivierroy        #+#    #+#             */
/*   Updated: 2023/09/15 11:44:53 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_output(void)
{
	t_tokens	*out;
	int			fd;

	fd = STDOUT_FILENO;
	out = ex()->out;
	while (out)
	{
		if (fd != STDOUT_FILENO)
			close_(fd);
		if (out->data->token_id == GREATGREAT)
			fd = open (out->data->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open (out->data->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(out->data->str);
			close_all();
			exit (EXIT_FAILURE);
		}
		ex()->fd[1] = fd;
		out = out->next;
	}
}
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

void	get_input(void)
{
	t_tokens	*in;
	int			fd;

	fd = STDIN_FILENO;
	in = ex()->in;
	while (in)
	{
		if (fd != STDIN_FILENO)
			close_(fd);
		if (in->data->token_id == LESSLESS)
			fd = open_heredoc(fd, in->data->str);
		else
		{
			fd = open (in->data->str, O_RDONLY);
			if (fd == -1)
			{
				perror(in->data->str);
				close_all();
				exit (EXIT_FAILURE);
			}
		}
		ex()->fd[0] = fd;
		in = in->next;
	}
}