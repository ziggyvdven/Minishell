/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:17:27 by oroy              #+#    #+#             */
/*   Updated: 2023/09/24 12:48:42 by oroy             ###   ########.fr       */
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
	t_tokens	*env;

	env = t()->env;
	while (env)
	{
		printf ("%s\n", env->data->str);
		env = env->next;
	}
}

// void	bt_export(void)
// {
// 	bool	setenv;
// 	char	*newentry;
// 	size_t	i;

// 	if (ex()->exec->next)
// 	{
// 		i = 0;
// 		setenv = false;
// 		while (ex()->exec->data->str[i])
// 		{
// 			if (ex()->exec->data->str[i] == '=')
// 				setenv = true;
// 			i++;
// 		}
// 		if (setenv)
// 		{
// 			newentry = ft_calloc(1, sizeof (char *));
// 		}
// 	}
// }

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
	// else if (ft_strlen(cmd) == 6 && !ft_strncmp(cmd, "export", 6))
	// 	bt_export();
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
