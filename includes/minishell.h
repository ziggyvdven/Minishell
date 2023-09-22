/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:40:58 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/22 13:03:31 by oroy             ###   ########.fr       */
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
# include <dirent.h>

/*MACROS***********************************************************************/

# define WORD			101
# define WORD_EXP		102
# define D_QUOTE_EXP	103
# define FLAG_EXP		104
# define MACRO			105

# define S_QUOTE		111
# define D_QUOTE		112
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
	int			saves[2];
	int			exitcode;
}	t_exec;

typedef struct s_expand
{
	char	**arr;
	char	*new_str;
	char	*temp;
	int		init;
	int		start;
	int		end;
	int		i;
	int		is_exp;
}	t_expand;

/*SIGNALS**********************************************************************/
void		sigint_handler(int signo);
void		sigquit_handler(int signo);
void		set_signals(void);

/*PARSING**********************************************************************/
t_tokens	*parse_input(char *input);
t_parsing	*pa(void);
bool		is_whitespace(char c);
t_tokens	*ft_expand_tokens(t_tokens *tokens);
bool		is_meta(char c);
int			ft_double_quote(char *input, int i);
int			ft_single_quote(char *input, int i);
int			ft_great(char *input, int i);
int			ft_less(char *input, int i);

/*BUILTIN**********************************************************************/
bool		is_builtin(char *cmd);
void		bt_cd(void);
void		bt_echo(void);

/*EXEC*************************************************************************/
t_exec		*ex(void);
void		close_(int fildes);
void		close_all(void);
void		close_tab(int fildes[2]);
void		create_cmd_ar(void);
int			dup_(int fildes);
int			dup2_(int fildes, int fildes2);
void		execute_cmds(t_tokens *tokens);
void		execve_(char *path, char **cmd, char **envp);
pid_t		fork_(void);
void		get_cmdpath(void);
char		*get_heredoc_input(char *delimiter);
void		get_input(void);
void		get_output(void);
int			open_heredoc(int fd, char *str);
void		pipe_(int fildes[2]);
void		waitpid_(pid_t pid, int *status, int options);

/*UTILS************************************************************************/
t_data		*get_data(char *ptr, int token_id);

/*STRUCTS**********************************************************************/
t_expand	*x(void);
t_parsing	*pa(void);

#endif