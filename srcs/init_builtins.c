/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:27 by oroy              #+#    #+#             */
/*   Updated: 2023/09/07 14:07:17 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*set_builtin(char *str, char **builtins)
{
	char	*bt;

	bt = ft_strdup(str);
	if (!bt)
	{
		ft_putendl_fd("Error: Couldn't malloc builtin", 2);
		ft_free_ar(builtins);
		exit(EXIT_FAILURE);
	}
	return (bt);
}

char	**init_builtins(void)
{
	char	**builtins;

	builtins = ft_calloc(8, sizeof (char *));
	if (!builtins)
	{
		ft_putendl_fd("Error: Couldn't malloc builtin array", 2);
		exit(EXIT_FAILURE);
	}
	builtins[0] = set_builtin("echo", builtins);
	builtins[1] = set_builtin("cd", builtins);
	builtins[2] = set_builtin("pwd", builtins);
	builtins[3] = set_builtin("export", builtins);
	builtins[4] = set_builtin("unset", builtins);
	builtins[5] = set_builtin("env", builtins);
	builtins[6] = set_builtin("exit", builtins);
	builtins[7] = NULL;
	return (builtins);
}
