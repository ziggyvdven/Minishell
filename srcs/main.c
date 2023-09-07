/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/07 12:15:17 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

//handels the sigint (crtl-C) signal (was: Quit/ now: new promt)

void sigint_handler() 
{
	rl_replace_line(" ", 0);
	rl_on_new_line();
	rl_redisplay();
}

//handels the sigint (crtl-/) signal (was: / now: new promt)

void sigquit_handler() 
{
	return;
}

void set_signals()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

int main()
{
	int i = 5;
	char *line;

	printf("\x1b[31m🔥🔥🔥WELCOME TO MINIHELL🔥🔥🔥🔥\x1b[0m\n");
	set_signals();
	while (i--)
	{
		line = (readline("Minishell: "));
		if (!line)
		{
			rl_replace_line("Minishell: exit", 10);
			break;
		}
		add_history(line);
		free(line);
		line = NULL;
	}
}
