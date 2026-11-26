/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prinft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:37:34 by marisous          #+#    #+#             */
/*   Updated: 2026/11/26 16:52:24 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>
/* %[argument$][flags][width][.precision][length modifier]conversion */
/* "-+0# " for bonus flags */
/* (minimum) width.precision */
/* argument and length modifier are not required */

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	va_list	*p_ap;
	int		retval;
	char	*cur;

	retval = 0;
	cur = (char *) format;
	va_start(ap, format);
	p_ap = &ap;
	while (*cur != '\0')
	{
		if (*cur == '%' && *(cur + 1) == '%')
		{
			ft_putchar_fd('%', 1);
			cur++;
		}
		else if (*cur != '%')
			ft_putchar_fd(*cur, 1);
		else
			cur += ft_handle_vargs(cur, p_ap, &retval);
		cur++;
		retval++;
	}
	va_end(ap);
	return (retval);
}
