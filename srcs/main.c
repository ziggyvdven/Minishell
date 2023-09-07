/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/07 17:10:59 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char *input;

	printf("\x1b[31m🔥🔥🔥WELCOME TO MINIHELL🔥🔥🔥🔥\x1b[0m\n");
	set_signals();
	while (1)
	{
		input = readline("Minishell: ");
		if (!input)
			break ;
		add_history(input);
		if (ft_strnstr("exit", input, 4) && !ft_strncmp(input, "exit", 4))
		{
			printf("exit\n");
			break ;
		}
		free(input);
		input = NULL;
		rl_replace_line("New promt", 0);
	}
}
