/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_dup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:05:32 by oroy              #+#    #+#             */
/*   Updated: 2023/09/29 12:33:02 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	dup_(int fildes)
{
	int	fildes2;

	fildes2 = dup (fildes);
	if (fildes2 == -1)
	{
		perror ("Problem with dup() call");
		close_all();
		// free_data();
	}
	return (fildes2);
}

int	dup2_(int fildes, int fildes2)
{
	int	fd;

	fd = dup2 (fildes, fildes2);
	if (fd == -1)
	{
		perror ("Problem with dup2() call");
		close_all();
		// free_data();
	}
	return (fd);
}
