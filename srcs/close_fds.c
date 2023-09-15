/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:29:39 by oroy              #+#    #+#             */
/*   Updated: 2023/09/14 21:42:39 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_(int fildes)
{
	// if (fildes > 2)
	// {
		if (close (fildes) == -1)
			perror ("Problem with close() call");
	// 	fildes = 0;
	// }
}

void	close_tab(int fildes[2])
{
	int	i;

	i = 0;
	while (i < 2 && fildes[i] > 2)
	{
		close_(fildes[i]);
		fildes[i] = 0;
		i++;
	}
}

void	close_all(void)
{
	close_tab(ex()->fd);
	close_tab(ex()->pipes);
}
