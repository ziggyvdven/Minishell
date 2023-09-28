/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:16:15 by oroy              #+#    #+#             */
/*   Updated: 2023/09/28 14:17:13 by zvan-de-         ###   ########.fr       */
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
			ft_putstr_exit("Error: Malloc failed", 2, 1);
		if (access (path, X_OK) == 0)
			return (path);
		ft_free_str(path);
		i++;
	}
	return (NULL);
}

void	get_cmdpath(void)
{
	char	**pathlist;
	char	*path;
	char	*temp;

	if (access (ex()->exec->data->str, X_OK) == 0)
	{
		ex()->cmdpath = ft_strdup(ex()->exec->data->str);
		return ;
	}
	path = ft_strjoin("/", ex()->exec->data->str);
	if (!path)
		ft_putstr_exit("Error: Malloc failed", 2, 1);
	temp = ft_get_env("PATH");
	pathlist = ft_split(temp, ':');
	free (temp);
	if (!pathlist)
	{
		ft_free_str(path);
		ft_putstr_exit("Error: Malloc failed", 2, 1);
	}
	ex()->cmdpath = find_cmd_location(pathlist, path);
	ft_free_ar(pathlist);
	ft_free_str(path);
	if (!ex()->cmdpath)
	{
		ft_putstr_fd(ex()->exec->data->str, 2);
		ft_putendl_fd(": command not found", 2);
		// free_data();
		exit (127);
	}
}
