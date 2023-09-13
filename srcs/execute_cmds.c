/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:39:30 by olivierroy        #+#    #+#             */
/*   Updated: 2023/09/12 23:26:42 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exec	*ex(void)
{
	static t_exec	ex;

	return (&ex);
}

int	get_output(void)
{
	t_tokens	*out;
	int			fd;

	fd = STDOUT_FILENO;
	out = ex()->out;
	while (out)
	{
		if (out->data->token_id == GREATGREAT)
			fd = open (out->data->str, O_RDONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open (out->data->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(out->data->str);
			exit (EXIT_FAILURE);
		}
		out = out->next;
	}
	return (fd);
}

int	get_input(void)
{
	t_tokens	*in;
	int			fd;

	fd = STDIN_FILENO;
	in = ex()->in;
	while (in)
	{
		fd = open (in->data->str, O_RDONLY);
		if (fd == -1)
		{
			perror(in->data->str);
			exit (EXIT_FAILURE);
		}
		in = in->next;
	}
	return (fd);
}

void	child_process(void)
{
	ex()->fd[0] = get_input();
	ex()->fd[1] = get_output();
	dup2 (ex()->fd[0], STDIN_FILENO);
	dup2 (ex()->fd[1], STDOUT_FILENO);
	if (ex()->fd[0] != STDIN_FILENO)
		close (ex()->fd[0]);
	if (ex()->fd[1] != STDOUT_FILENO)
		close (ex()->fd[1]);
	get_cmd_info();
	create_cmd_ar();
	execve (ex()->cmdpath, ex()->cmd, NULL);
	exit (EXIT_FAILURE);
}

void	parent_process(t_tokens *token)
{
	pid_t	process_id;

	if (token)
		pipe(ex()->pipes);
	process_id = fork();
	if (process_id == 0)
		child_process();
	waitpid (process_id, NULL, 0);
	ft_free_ar(ex()->cmd);
	ft_free_str(ex()->cmdpath);
	ft_lstclear(&ex()->in);
	ft_lstclear(&ex()->out);
	ft_lstclear(&ex()->exec);
	if (token)
	{
		close(ex()->pipes[0]);
		close(ex()->pipes[1]);
	}
}

void	execute_cmds(t_tokens *tokens)
{
	t_tokens	*temp = NULL;

	while (tokens)
	{
		if (tokens->data->token_id == PIPE && !temp)
			ft_putstr_exit("syntax error near unexpected token `|'", 2, 1);
		temp = ft_lstnew(tokens->data);
		if (!temp)
			ft_putstr_exit("Error: Malloc failed", 2, 1);
		if (tokens->data->token_id == WORD
			|| tokens->data->token_id == FLAG
			|| tokens->data->token_id == S_QUOTE
			|| tokens->data->token_id == D_QUOTE)
			ex()->exec = ft_lstadd_back(ex()->exec, temp);
		else if (tokens->data->token_id == GREAT)
		{
			ft_lstdelone(temp);
			tokens = tokens->next;
			if (tokens)
			{
				temp = ft_lstnew(tokens->data);
				if (!temp)
					ft_putstr_exit("Error: Malloc failed", 2, 1);
				printf ("%s\n", temp->data->str);
				ex()->in = ft_lstadd_back(ex()->in, temp);
			}
			else
				break ;
		}
		else if (tokens->data->token_id == GREATGREAT)
			printf ("Do heredoc");
		else if (tokens->data->token_id == LESS
			|| tokens->data->token_id == LESSLESS)
		{
			ft_lstdelone(temp);
			tokens = tokens->next;
			if (tokens)
			{
				temp = ft_lstnew(tokens->data);
				if (!temp)
					ft_putstr_exit("Error: Malloc failed", 2, 1);
				ex()->out = ft_lstadd_back(ex()->out, temp);
			}
			else
				break ;
		}
		else if (tokens->data->token_id == PIPE)
			parent_process(tokens);
		tokens = tokens->next;
	}
	parent_process(tokens);
}
