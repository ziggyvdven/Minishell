/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:42:05 by olivierroy        #+#    #+#             */
/*   Updated: 2023/10/04 15:25:16 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(void)
{
	if (access ("heredoc", F_OK) == 0)
		unlink ("heredoc");
	ft_free_ar(ex()->cmd);
	ft_free_str(ex()->cmdpath);
	ft_clearlst(&ex()->in);
	ft_clearlst(&ex()->out);
	ft_clearlst(&ex()->exec);
}

void	exits(void)
{
	ft_lstclear(&t()->env);
	ft_lstclear(&t()->tokens);
	free_cmd();
	ft_free_str(t()->input);
}
