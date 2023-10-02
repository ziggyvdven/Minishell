/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:39 by oroy              #+#    #+#             */
/*   Updated: 2023/10/02 15:01:07 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_(int fildes)
{
	if (fildes > 2)
	{
		if (close (fildes) == -1)
			perror ("Problem with close() call");
		fildes = 0;
	}
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
	close_(ex()->save);
}
