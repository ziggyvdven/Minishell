/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/06 17:49:34 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <signal.h>

void sigint_handler() 
{
    readline("Minishell: ");
}

void sigkill_handler() 
{
   return;
}

void set_signals()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigkill_handler);
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
		add_history(line);
		free(line);
		line = NULL;
		// Test Github
		// Test ziggy branch
	}
}
