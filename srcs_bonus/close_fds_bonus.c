/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:39 by oroy              #+#    #+#             */
/*   Updated: 2023/09/29 12:32:54 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

void	close_(int fildes)
{
	if (close (fildes) == -1)
		perror ("Problem with close() call");
}

void	close_tab(int fildes[2])
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (fildes[i] > 2)
		{
			close_(fildes[i]);
			fildes[i] = 0;
		}
		i++;
	}
}

void	close_all(void)
{
	close_tab(ex()->fd);
	close_tab(ex()->pipes);
	close_tab(ex()->saves);
}
