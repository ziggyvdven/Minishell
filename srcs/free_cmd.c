/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:42:05 by olivierroy        #+#    #+#             */
/*   Updated: 2023/10/02 16:38:18 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd(void)
{
	if (access ("heredoc", F_OK) == 0)
		unlink ("heredoc");
	// ft_free_ar(t()->env_arr);
	ft_free_ar(ex()->cmd);
	ft_free_str(ex()->cmdpath);
	ft_clearlst(&ex()->in);
	ft_clearlst(&ex()->out);
	ft_clearlst(&ex()->exec);
}
