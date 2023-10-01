/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:32:59 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/30 23:06:49 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//handels the sigint (crtl-C) signal (was: Quit/ now: new promt)

void	sigint_handler(int signo)
{
	(void) signo;
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
	write(1, "\n", 1);
	exit(1);
}

void	silence_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	set_here_sig(void)
{
	struct sigaction	action;

	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	action.sa_handler = heredoc_signals;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	return ;
}

void	set_signals(void)
{
	struct sigaction	action;

	ex()->signal = 0;
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	action.sa_handler = sigint_handler;
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	return ;
}
