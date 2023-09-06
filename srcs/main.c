/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */

/*   Updated: 2023/09/06 14:31:46 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

int main()
{
	int i = 5;
	char *line;
	
	printf("\x1b[31m🔥🔥🔥WELCOME TO MINIHELL🔥🔥🔥🔥\x1b[0m\n");
	while (i--)
	{
		line = (readline("Minishell: "));
		free(line);
		line = NULL;
		// Test Github
		// Test Olivier Branch

	}
}
