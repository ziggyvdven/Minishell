/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:40:58 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/08 12:55:35 by zvan-de-         ###   ########.fr       */
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

# define WORD		101
# define CMD		102
# define MARCO		103

# define PIPE		110
# define S_QUOTE	111
# define D_QUOTE	112
# define FLAG		113

# define GREAT		131			
# define LESS		132 			
# define GREATGREAT	133 	
# define LESSLESS	134

/*SIGNALS**********************************************************************/
void		sigint_handler(int signo);
void		sigquit_handler(int signo);
void		set_signals(void);

/*PARSING**********************************************************************/
char		**init_builtins(void);
void		parse_input(char *input);

/*UTILS**********************************************************************/
t_data		*get_data(char *ptr, int token_id);

#endif