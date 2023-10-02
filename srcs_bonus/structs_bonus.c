/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:06:01 by zvandeven         #+#    #+#             */
/*   Updated: 2023/09/29 12:33:40 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

t_exec	*ex(void)
{
	static t_exec	ex;

	return (&ex);
}

t_parsing	*pa(void)
{
	static t_parsing	parsing;

	return (&parsing);
}

t_env	*t(void)
{
	static t_env	t;

	return (&t);
}

t_expand	*x(void)
{
	static t_expand	exp;

	if (exp.init == 0)
	{
		exp.init = 1;
		exp.i = 0;
		exp.start = 0;
		exp.end = -1;
		exp.is_exp = 0;
		exp.new_str = NULL;
		exp.temp = NULL;
	}
	return (&exp);
}
