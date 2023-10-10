/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:41:55 by olivierroy        #+#    #+#             */
/*   Updated: 2023/10/06 12:00:24 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	open_output(t_data *output)
{
	if (output->token_id == GREATGREAT)
		return (open (output->str, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else
		return (open (output->str, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

bool	get_output(void)
{
	t_tokens	*out;
	int			fd;

	fd = STDOUT_FILENO;
	out = ex()->out;
	while (out)
	{
		if (fd != STDOUT_FILENO)
			close_(fd);
		fd = open_output(out->data);
		if (fd == -1)
		{
			ex()->fd[1] = STDOUT_FILENO;
			perror(out->data->str);
			ex()->exitcode = 1;
			close_all();
			free_cmd();
			return (false);
		}
		ex()->fd[1] = fd;
		out = out->next;
	}
	return (true);
}

bool	get_input(void)
{
	t_tokens	*in;
	int			fd;

	fd = STDIN_FILENO;
	in = ex()->in;
	while (in)
	{
		if (fd != STDIN_FILENO)
			close_(fd);
		fd = open (in->data->str, O_RDONLY);
		if (fd == -1)
		{
			ex()->fd[0] = STDIN_FILENO;
			perror(in->data->str);
			ex()->exitcode = 1;
			close_all();
			free_cmd();
			return (false);
		}
		ex()->fd[0] = fd;
		in = in->next;
	}
	return (true);
}
