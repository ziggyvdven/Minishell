/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/10/06 12:25:03 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens;
	char		*input;

	set_env(argc, argv, envp);
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
		t()->tokens = tokens;
		if (tokens && pa()->parse_error == 0)
			execute_cmds(tokens);
		ft_lstclear(&tokens);
		ft_free_str(input);
		if (access ("heredocHeredocheredoc", F_OK) == 0)
			unlink ("heredocHeredocheredoc");
	}
	ft_lstclear(&t()->env);
}
