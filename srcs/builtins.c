/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:27 by oroy              #+#    #+#             */
/*   Updated: 2023/09/22 19:22:43 by oroy             ###   ########.fr       */
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
void	bt_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf ("%s\n", pwd);
	ft_free_str(pwd);
}

void	bt_env(void)
{
	size_t	i;

	i = 0;
	while (env()->env[i])
	{
		printf ("%s\n", env()->env[i]);
		i++;
	}
}

void	bt_export(void)
{
	
}

bool	is_builtin(char *cmd)
{
	int	status;

	status = true;
	if (ft_strlen(cmd) == 4 && !ft_strncmp(cmd, "echo", 4))
		bt_echo();
	else if (ft_strlen(cmd) == 2 && !ft_strncmp(cmd, "cd", 2))
		bt_cd();
	else if (ft_strlen(cmd) == 3 && !ft_strncmp(cmd, "pwd", 3))
		bt_pwd();
	else if (ft_strlen(cmd) == 6 && !ft_strncmp(cmd, "export", 6))
		bt_export();
	// else if (cmd == "unset")
	// 	printf ("Do unset()");
	else if (ft_strlen(cmd) == 3 && !ft_strncmp(cmd, "env", 3))
		bt_env();
	// else if (cmd == "exit")
	// 	printf ("Do exit()");
	else
		status = false;
	return (status);
}
