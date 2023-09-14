/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:16:15 by oroy              #+#    #+#             */
/*   Updated: 2023/09/13 14:17:29 by olivierroy       ###   ########.fr       */
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

	path = ft_strjoin("/", ex()->exec->data->str);
	if (!path)
		ft_putstr_exit("Error: Malloc failed", 2, 1);
	pathlist = ft_split(getenv("PATH"), ':');
	if (!pathlist)
	{
		ft_free_str(path);
		ft_putstr_exit("Error: Malloc failed", 2, 1);
	}
	ex()->cmdpath = find_cmd_location(pathlist, path);
	ft_free_ar(pathlist);
	ft_free_str(path);
	// if (!ex()->cmdpath)
	// {
	// 	ft_putstr_fd("Error: Shell command not found/executable: ", 2);
	// 	ft_putendl_fd(arg, 2);
	// 	free_data();
	// 	exit (EXIT_FAILURE);
	// }
}
