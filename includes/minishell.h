/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:40:58 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/10/02 11:53:20 by zvan-de-         ###   ########.fr       */
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
# include <errno.h>
# include <signal.h>

/*MACROS***********************************************************************/

# define WORD_EXP		102
# define D_QUOTE_EXP	103
# define FLAG_EXP		104
# define MACRO			105
# define WSPACE			106

# define WORD			110
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
	bool		space;
	int			parse_error;
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
	int			signal;
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

typedef struct s_env
{
	t_tokens	*env;
}	t_env;

/*SIGNALS**********************************************************************/
void		sigint_handler(int signo);
void		sigquit_handler(int signo);
void		set_signals(void);
void		heredoc_signals(int signo);
void		set_here_sig(void);
void		silence_signal(void);

/*PARSING**********************************************************************/
t_tokens	*parse_input(char *input);
int			meta_specifier(char *input, int i);
int			ft_double_quote(char *input, int i);
int			ft_single_quote(char *input, int i);
int			ft_less_great(char *input, int i);
int			get_wspace(char *input, int i);
int			get_word(char *input, int i);
int			get_flag(char *input, int i);
t_tokens	*ft_expand_tokens(t_tokens *tokens);
t_tokens	*ft_concat_tokens(t_tokens *t);

/*BUILTIN**********************************************************************/
bool		is_builtin(char *cmd);
void		bt_cd(void);
void		bt_echo(void);
void		bt_export(void);
void		bt_unset(void);
void		bt_env(void);

/*ENV**************************************************************************/
void		set_env(char **envp);
char		*ft_get_env(char *str);
void		ft_print_env(t_tokens *env);
int			ft_env_replace(t_tokens *env, char *str);
void		unset(t_tokens	*env, t_tokens	*head, t_tokens	*args);

/*EXEC*************************************************************************/
t_exec		*ex(void);
void		close_(int fildes);
void		close_all(void);
void		close_tab(int fildes[2]);
void		create_cmd_ar(void);
int			dup_(int fildes);
int			dup2_(int fildes, int fildes2);
void		execute_cmds(t_tokens *tokens);
int			exec_error(char *s, int exitcode);
void		execve_(char *path, char **cmd, char **envp);
void		free_cmd(void);
pid_t		fork_(void);
void		get_cmdpath(void);
char		*get_heredoc_input(char *delimiter);
void		get_input(void);
void		get_output(void);
void		parent_process(t_tokens *token);
void		pipe_(int fildes[2]);
void		waitpid_(pid_t pid, int *status, int options);

/*UTILS************************************************************************/
t_data		*get_data(char *ptr, int token_id);
bool		is_meta(char c);
void		pars_error_(char *str, int fd);

/*STRUCTS**********************************************************************/
t_parsing	*pa(void);
t_env		*t(void);
t_expand	*x(void);

#endif