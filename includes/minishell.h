/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivierroy <olivierroy@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:40:58 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/12 23:23:09 by olivierroy       ###   ########.fr       */
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

# define PIPE			110
# define S_QUOTE		111
# define D_QUOTE		112
# define D_QUOTE_EXP	113
# define FLAG			114

# define GREAT			131			
# define LESS			132 			
# define GREATGREAT		133 	
# define LESSLESS		134

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
void    create_cmd_ar(void);
void    execute_cmds(t_tokens *tokens);
void	get_cmd_info(void);

/*UTILS**********************************************************************/
t_data		*get_data(char *ptr, int token_id);

#endif