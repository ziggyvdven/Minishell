/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_custom.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:16:04 by oroy              #+#    #+#             */
/*   Updated: 2023/10/02 15:31:44 by zvan-de-         ###   ########.fr       */
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

int	ft_putstr_excode(char *str, int fd, int exit_status)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		write(fd, &str[i], 1);
	ex()->exitcode = exit_status;
	return (1);
}
