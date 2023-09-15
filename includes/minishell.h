/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:40:58 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/14 17:29:56 by olivierroy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

/*MACROS***********************************************************************/

# define WORD			101
# define CMD			102
# define MACRO			103

# define S_QUOTE		111
# define D_QUOTE		112
# define D_QUOTE_EXP	113
# define FLAG			114

# define PIPE			130
# define LESS			131
# define GREAT			132
# define LESSLESS		133
# define GREATGREAT		134

typedef struct s_parsing
{
	int			id;
	int			j;
	int			i;
}	t_parsing;

typedef struct s_exec
{
	t_tokens	*in;
	t_tokens	*out;
	t_tokens	*exec;
	char		**cmd;
	char		*cmdpath;
	int			fd[2];
	int			pipes[2];
}	t_exec;

/*SIGNALS**********************************************************************/
void		sigint_handler(int signo);
void		sigquit_handler(int signo);
void		set_signals(void);

/*PARSING**********************************************************************/
char		**init_builtins(void);
t_tokens	*parse_input(char *input);
t_parsing	*pa(void);

/*EXEC*************************************************************************/
t_exec	*ex(void);
void	close_(int fildes);
void	close_all(void);
void	close_tab(int fildes[2]);
void    create_cmd_ar(void);
int		dup_(int fildes);
void	dup2_(int fildes, int fildes2);
void    execute_cmds(t_tokens *tokens);
void	execve_(char *path, char **cmd, char **envp);
pid_t	fork_(void);
void	get_cmdpath(void);
void	pipe_(int fildes[2]);
void	waitpid_(pid_t pid, int *status, int options);

/*UTILS**********************************************************************/
t_data		*get_data(char *ptr, int token_id);

#endif