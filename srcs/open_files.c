/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:41:55 by olivierroy        #+#    #+#             */
/*   Updated: 2023/09/14 14:42:46 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	get_output(void)
// {
// 	t_tokens	*out;
// 	int			fd;

// 	fd = STDOUT_FILENO;
// 	out = ex()->out;
// 	while (out)
// 	{
// 		if (out->data->token_id == GREATGREAT)
// 			fd = open (out->data->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		else
// 			fd = open (out->data->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd == -1)
// 		{
// 			perror(out->data->str);
// 			close_all();
// 			exit (EXIT_FAILURE);
// 		}
// 		out = out->next;
// 	}
// 	return (fd);
// }

// int	get_input(void)
// {
// 	t_tokens	*in;
// 	int			fd;

// 	if (ex()->fd[0] != STDIN_FILENO)
// 		fd = ex()->fd[0];
// 	else
// 		fd = STDIN_FILENO;
// 	in = ex()->in;
// 	while (in)
// 	{
// 		fd = open (in->data->str, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror(in->data->str);
// 			close_all();
// 			exit (EXIT_FAILURE);
// 		}
// 		in = in->next;
// 	}
// 	return (fd);
// }