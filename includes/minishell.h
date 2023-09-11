/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvandeven <zvandeven@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:40:58 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/11 15:54:33 by zvandeven        ###   ########.fr       */
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

/*SIGNALS**********************************************************************/
void		sigint_handler(int signo);
void		sigquit_handler(int signo);
void		set_signals(void);

/*PARSING**********************************************************************/
char		**init_builtins(void);
void		parse_input(char *input);
t_parsing	*pa(void);

/*UTILS**********************************************************************/
t_data		*get_data(char *ptr, int token_id);

#endif