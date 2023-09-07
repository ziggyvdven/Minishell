/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:32:59 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/07 14:47:35 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//handels the sigint (crtl-C) signal (was: Quit/ now: new promt)

void	sigint_handler(int signo)
{
	(void) signo;
	rl_redisplay();
	printf("\nMinishell: ");
	return ;
}

//handels the sigint (crtl-/) signal (was: / now: new promt)

void	sigquit_handler(int signo)
{
	(void) signo;
	rl_redisplay();
	return ;
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	return ;
}
