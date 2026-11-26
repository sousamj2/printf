/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 16:47:54 by marisous          #+#    #+#             */
/*   Updated: 2026/11/26 17:05:15 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_str_formatted(char *s, t_format *fconf)
{
	int		nspaces;
	int		len;

	if (s == NULL)
		s = "(null)";
	len = (int) ft_strlen(s);
	if (0 <= fconf->prec && fconf->prec < len)
		len = fconf->prec;
	nspaces = fconf->width - len;
	if (nspaces < 0)
		nspaces = 0;
	if (!(fconf->flag & FLAG_MINUS))
		ft_putchars_n_fd(' ', 1, nspaces);
	ft_putstr_fd_n(s, 1, len);
	if (fconf->flag & FLAG_MINUS)
		ft_putchars_n_fd(' ', 1, nspaces);
	return (len + nspaces);
}

void	ft_putstr_fd_n(const char *s, int fd, int n)
{
	int	index;

	index = 0;
	while (*s != '\0' && index < n)
	{
		ft_putchar_fd(*s, fd);
		s++;
		index++;
	}
}

void	ft_putchars_n_fd(const char c, int fd, int n)
{
	int	index;

	index = 0;
	while (index < n)
	{
		ft_putchar_fd(c, fd);
		index++;
	}
}
