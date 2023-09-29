/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:32:59 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/29 17:12:18 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//handels the sigint (crtl-C) signal (was: Quit/ now: new promt)

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	heredoc_signals(int signo)
{
	(void) signo;
	write(1, "\0", 1);
	close(1);
	exit(0);
}

void	set_here_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, heredoc_signals);
}

void	set_signals(void)
{
	struct sigaction	action;

	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	action.sa_handler = sigint_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	return ;
}
