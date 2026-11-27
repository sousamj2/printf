/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variadic_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 16:51:31 by marisous          #+#    #+#             */
/*   Updated: 2026/11/26 23:38:07 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_handle_vargs(char *cur, va_list *ap, int *retval)
{
	t_format	fconf;
	char		*next;
	t_format	*ptr_fc;

	fconf.prec = -1;
	fconf.width = -1;
	fconf.flag = 0;
	fconf.opt = '\0';
	ptr_fc = &fconf;
	next = (char *)ft_next_conv(cur, ptr_fc);
	fconf.opt = *next;
	if (fconf.opt == 'c')
		*retval += ft_char_formatted(va_arg(*ap, int)) - 1;
	else if (fconf.opt == 's')
		*retval += ft_str_formatted(va_arg(*ap, char *), ptr_fc) - 1;
	else if (fconf.opt == 'p')
		*retval += ft_itoa_formatted((unsigned long long)va_arg(*ap, void *),
				ptr_fc) - 1 ;
	else if (ft_tolower(fconf.opt) == 'x')
		*retval += ft_itoa_formatted(va_arg(*ap, unsigned int), ptr_fc) - 1;
	else if (ft_tolower(fconf.opt) == 'u')
		*retval += ft_itoa_formatted(va_arg(*ap, unsigned int), ptr_fc) - 1;
	else
		*retval += ft_itoa_formatted(va_arg(*ap, int), ptr_fc) - 1;
	return (next - cur);
}

char	*ft_next_conv(char *c, t_format *fconf)
{
	while (*c != '\0')
	{
		if (*c == 'c' || *c == 's' || *c == 'p' || *c == 'd' || *c == 'i'
			|| *c == 'u' || *c == 'x' || *c == 'X')
			return (c);
		else if (*c == '.')
			fconf->prec = ft_atoi(c + 1);
		else if (*c >= '1' && *c <= '9' && fconf->prec < 0)
		{
			fconf->width = ft_atoi(c);
			c += (ft_strlen(ft_itoa(fconf->width)) - 1);
		}
		else if (*c == '#')
			fconf->flag |= FLAG_HASH;
		else if (*c == '0')
			fconf->flag |= FLAG_ZERO;
		else if (*c == '-')
			fconf->flag |= FLAG_MINUS;
		else if (*c == ' ')
			fconf->flag |= FLAG_SPACE;
		else if (*c == '+')
			fconf->flag |= FLAG_PLUS;
		c++;
	}
	return (NULL);
}
