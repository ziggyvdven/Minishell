/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_custom.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:16:04 by oroy              #+#    #+#             */
/*   Updated: 2023/09/29 13:16:21 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pars_error_(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	pa()->parse_error = 1;
}

int	exec_error(char *s, int exitcode)
{
	if (exitcode == 127)
	{
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else
	{
		if (exitcode > 1)
			ft_putstr_fd("Parse error near ", 2);
		ft_putendl_fd(s, 2);
	}
	free_cmd();
	ex()->exitcode = exitcode;
	return (exitcode);
}
