/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 18:14:23 by marisous          #+#    #+#             */
/*   Updated: 2026/11/23 18:14:27 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd_n(const char *s, int fd, int n)
{
	int index;

	index = 0;
	while (*s != '\0' && index < n)
	{
		ft_putchar_fd(*s, fd);
		s++;
		index++;
	}
}
