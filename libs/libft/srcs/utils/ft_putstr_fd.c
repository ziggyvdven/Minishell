/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvan-de- <zvan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:58:11 by zvandeven         #+#    #+#             */
/*   Updated: 2023/09/07 14:37:43 by zvan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	putstr_exit(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		write(fd, &str[i], 1);
	exit(fd);
}

// int main(int argc, char **argv)
// {
// 	if (argc == 2)
// 	ft_putstr_fd(argv[1], 1);
// 	printf("\n");
// }
