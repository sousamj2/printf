/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchars_n_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 18:32:34 by marisous          #+#    #+#             */
/*   Updated: 2026/11/23 21:59:10 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchars_n_fd(const char c, int fd, int n)
{
	int index;

	index = 0;
	while (index < n)
	{
		ft_putchar_fd(c, fd);
		index++;
	}
}
