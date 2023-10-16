/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/10/16 12:16:20 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens;
	char		*input;

	set_env(argc, argv, envp);
	set_signals();
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
		else 
			ex()->exitcode = 1;
		ft_lstclear(&tokens);
		ft_free_str(input);
		if (access ("heredocHeredocheredoc", F_OK) == 0)
			unlink ("heredocHeredocheredoc");
	}
	printf("exit\n");
	ft_lstclear(&t()->env);
}
