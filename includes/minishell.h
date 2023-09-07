/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:40:58 by zvan-de-          #+#    #+#             */
/*   Updated: 2023/09/07 13:19:21 by oroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	"../libs/libft/includes/libft.h"
# include	<stdio.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<limits.h>
# include	<fcntl.h>
# include	<readline/readline.h>
# include	<sys/wait.h>

// typedef struct s_data
// {
// 	char	**cmd;
// 	char	*cmdpath;
// 	char	**pathlist;
// 	int		files[2];
// 	int		pipes[2];
// }	t_data;

/*CHECKS*********************************/

/*INIT**********************************/

char	**init_builtins(void);

/*ERRORS******************************/

#endif