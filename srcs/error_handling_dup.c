/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_dup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:05:32 by oroy              #+#    #+#             */
/*   Updated: 2023/09/29 12:06:11 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_(int fildes)
{
	int	fildes2;

	fildes2 = dup (fildes);
	if (fildes2 == -1)
	{
		perror ("Problem with dup() call");
		close_all();
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
	}
	return (fd);
}
