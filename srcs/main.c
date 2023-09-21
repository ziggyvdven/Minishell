/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/21 13:09:18 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_tokens	*tokens;
	char		*input;

	set_signals();
	printf("\x1b[31m🔥🔥🔥WELCOME TO MINIHELL🔥🔥🔥🔥\x1b[0m\n");
	while (1)
	{
		input = readline("Minishell: ");
		if (!input)
			break ;
		add_history(input);
		if (ft_strnstr("exit", input, 4) && !ft_strncmp(input, "exit", 4))
			ft_putstr_exit("exit\n", 1, 0);
		tokens = parse_input(input);
		execute_cmds(tokens);
		ft_lstclear(&tokens);
		ft_free_str(input);
	}
}
