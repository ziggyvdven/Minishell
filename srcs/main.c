/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/07 14:24:24 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_builtin(char **cmd, char **builtins)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(cmd[0]);
	while (builtins[i])
	{
		if (ft_strncmp(cmd[0], builtins[i], len) == 0)
			break;
		i++;
	}
	return (i);
}

// void	exec_sys_cmd(char **cmd)
// {
// 	dup2_(pipex->files[0], STDIN_FILENO);
// 	if (remaining_cmds > 1)
// 		dup2_(pipex->pipes[1], STDOUT_FILENO);
// 	else
// 	{
// 		open_outfile(argc, argv);
// 		dup2_(pipex->files[1], STDOUT_FILENO);
// 	}
// 	close_all();
// 	get_cmd_info(argv[argc - remaining_cmds - 1]);
// 	execve_(pipex->cmdpath, pipex->cmd, NULL);
// }

char	*get_input(char *cmd)
{
	int		input;
	char	*ptr;

	ptr = ft_strchr(cmd, '<');
	if (ptr)
	{
		ptr++;
		while (*ptr == ' ')
			ptr++;
	}
	return (ptr);
}

void	process_cmds(char **cmds, char **builtins)
{
	// int		pipes[2];
	// pid_t	process;
	int		input;
	char	**cmd;
	int		idx;

	while (*cmds)
	{
		input = open(get_input(*cmds), O_RDONLY);
		if (!input)
		{
			perror("Error");
			continue;
		}
		cmd = ft_split(*cmds, ' ');
		if (!cmd)
		{
			ft_putendl_fd("Error: Malloc failed", 2);
			exit(EXIT_FAILURE);
		}
		idx = check_for_builtin(cmd, builtins);
		// if (!builtins[idx])
		// {
		// 	if (*(*cmd + 1))
		// 		pipe(pipes);
		// 	process = fork();
		// 	if (process == 0)
		// 		exec_sys_cmd(cmd);
		// 	waitpid(process, NULL, 0);
		// }
		cmds++;
	}
}

int main()
{
	char	**builtins;
	char	**cmds;
	char	*line;
	int		i;
	
	i = 0;
	builtins = init_builtins();
	printf("\x1b[31m🔥🔥🔥WELCOME TO MINIHELL🔥🔥🔥🔥\x1b[0m\n");
	while (1)
	{
		line = readline("Minishell: ");
		if (!line)
			continue;
		add_history(line);
		cmds = ft_split(line, '|');
		ft_free_str(line);
		if (!cmds)
		{
			ft_putendl_fd("Error: Malloc failed", 2);
			exit(EXIT_FAILURE);
		}
		process_cmds(cmds, builtins);
		ft_free_ar(cmds);
	}
}
