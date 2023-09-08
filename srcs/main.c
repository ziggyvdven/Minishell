/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:19:45 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/07 17:55:41 by zvan-de-         ###   ########.fr       */
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
			break ;
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

	(void)input;
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

int main(void)
{
	char	**builtins;
	char	**cmds;
	char	*input;
	int		i;

	i = 0;
	builtins = init_builtins();
	set_signals();
	printf("\x1b[31m🔥🔥🔥WELCOME TO MINIHELL🔥🔥🔥🔥\x1b[0m\n");
	while (1)
	{
		input = readline("Minishell: ");
		if (!input)
			break ;
		add_history(input);
		if (ft_strnstr("exit", input, 4) && !ft_strncmp(input, "exit", 4))
		{
			printf("exit\n");
			break ;
		}
		cmds = ft_split(input, '|');
		if (!cmds)
		{
			ft_putendl_fd("Error: Malloc failed", 2);
			exit(EXIT_FAILURE);
		}
		ft_free_str(input);
		process_cmds(cmds, builtins);
		ft_free_ar(cmds);
	}
}
