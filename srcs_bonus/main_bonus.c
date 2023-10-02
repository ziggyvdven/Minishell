/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/29 12:33:19 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens;
	char		*input;

	(void) argc;
	(void) argv;
	set_env(envp);
	set_signals();
	printf("\x1b[31m🔥🔥🔥WELCOME TO MINIHELL🔥🔥🔥🔥\x1b[0m\n");
	while (1)
	{
		pa()->parse_error = 0;
		input = readline("Minishell: ");
		if (!input)
			break ;
		add_history(input);
		tokens = parse_input(input);
		if (tokens && pa()->parse_error == 0)
			execute_cmds(tokens);
		ft_lstclear(&tokens);
		ft_free_str(input);
	}
	ft_lstclear(&t()->env);
}