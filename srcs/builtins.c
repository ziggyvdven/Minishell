/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:27 by oroy              #+#    #+#             */
/*   Updated: 2023/09/22 18:34:14 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	bt_echo(void)
{
	t_tokens	*bt;
	int			newline;

	newline = 1;
	bt = ex()->exec->next;
	if (bt)
	{
		if (!ft_strncmp(bt->data->str, "-n", 2))
		{
			newline = 0;
			bt = bt->next;
		}
		while (bt)
		{
			printf ("%s", bt->data->str);
			bt = bt->next;
			if (bt)
				printf (" ");
		}
	}
	if (newline)
		printf ("\n");
	ex()->exitcode = 0;
}

void	bt_cd(void)
{
	DIR		*dir;
	char	*path;

	if (!ex()->exec->next)
		return ;
	path = ex()->exec->next->data->str;
	dir = opendir (path);
	if (!dir)
	{
		perror (path);
		ex()->exitcode = 1;
	}
	else
	{
		chdir (path);
		closedir (dir);
	}
}

bool	is_builtin(char *cmd)
{
	int	status;

	status = true;
	if (ft_strlen(cmd) == 4 && !ft_strncmp(cmd, "echo", 4))
		bt_echo();
	else if (ft_strlen(cmd) == 2 && !ft_strncmp(cmd, "cd", 2))
		bt_cd();
	// else if (cmd == "pwd")
	// 	printf ("Do pwd()");
	// else if (cmd == "export")
	// 	printf ("Do export()");
	// else if (cmd == "unset")
	// 	printf ("Do unset()");
	// else if (cmd == "env")
	// 	printf ("Do env()");
	// else if (cmd == "exit")
	// 	printf ("Do exit()");
	else
		status = false;
	return (status);
}

// bool	is_builtin(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (ex()->bt[i])
// 	{
// 		if (str == ex()->bt[i])
// 		{
// 			exec_builtin(str);
// 			return (true);
// 		}
// 		i++;
// 	}
// 	return (false);
// }
// static char	*set_builtin(char *str)
// {
// 	char	*bt;

// 	bt = ft_strdup(str);
// 	if (!bt)
// 	{
// 		ft_putendl_fd("Error: Couldn't malloc builtin", 2);
// 		ft_free_ar(ex()->bt);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (bt);
// }

// void	init_builtins(void)
// {
// 	ex()->bt = ft_calloc(8, sizeof (char *));
// 	if (!ex()->bt)
// 	{
// 		ft_putendl_fd("Error: Couldn't malloc builtin array", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	ex()->bt[0] = set_builtin("echo");
// 	ex()->bt[1] = set_builtin("cd");
// 	ex()->bt[2] = set_builtin("pwd");
// 	ex()->bt[3] = set_builtin("export");
// 	ex()->bt[4] = set_builtin("unset");
// 	ex()->bt[5] = set_builtin("env");
// 	ex()->bt[6] = set_builtin("exit");
// 	ex()->bt[7] = NULL;
// }
