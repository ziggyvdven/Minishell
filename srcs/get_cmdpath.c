/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:16:15 by oroy              #+#    #+#             */
/*   Updated: 2023/10/02 12:55:56 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_cmd_location(char **pathlist, char *cmd)
{
	char	*path;
	size_t	i;

	i = 0;
	while (pathlist[i])
	{
		path = ft_strjoin(pathlist[i], cmd);
		if (!path)
		{
			ft_free_ar(pathlist);
			ft_free_str(cmd);
			exit (exec_error("Malloc error", 1));
		}
		if (access (path, X_OK) == 0)
			return (path);
		ft_free_str(path);
		i++;
	}
	return (NULL);
}

static bool	check_initialpath(char *str)
{
	if (access (str, X_OK) == 0)
	{
		ex()->cmdpath = ft_strdup(str);
		return (true);
	}
	return (false);
}

void	get_cmdpath(void)
{
	char	**pathlist;
	char	*cmdpath;
	char	*path;
	char	*env;

	if (check_initialpath(ex()->exec->data->str))
		return ;
	path = ft_strjoin("/", ex()->exec->data->str);
	if (!path)
		exit (exec_error("Malloc error", 1));
	env = ft_get_env("PATH");
	pathlist = ft_split(env, ':');
	ft_free_str(env);
	if (!pathlist)
	{
		ft_free_str(path);
		exit (exec_error("Malloc error", 1));
	}
	cmdpath = find_cmd_location(pathlist, path);
	ft_free_ar(pathlist);
	ft_free_str(path);
	if (!cmdpath)
		exit (exec_error(ex()->exec->data->str, 127));
	ex()->cmdpath = cmdpath;
}
