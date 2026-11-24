/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prinft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:37:34 by marisous          #+#    #+#             */
/*   Updated: 2026/11/24 10:57:14 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_prinft(const char *format, ...)
{
	va_list	ap;
	va_list	*p_ap;
	int		retval;
	/* %[argument$][flags][width][.precision][length modifier]conversion */
	/* "-+0# " for bonus flags */
	/* (minimum) width.precision */
	/* argument and length modifier are not required */ 	
 	va_start(ap, format);
	p_ap = &ap;
	while (*format != '\0')
	{
		if (*format == '%' && *(format + 1) == '%')
		{
			ft_putchar_fd('%', 1);
			format++;
		}
		else if (*format == '%')		
			ft_putchar_fd(*format, 1);
		else
			ft_handle_vargs(format, p_ap);
		format++;
	}
	va_end(ap);
	return (0);
}

int	ft_handle_vargs(const char *format, va_list *ap)
{
	t_format fconf;
	char *next;
	int retval;
	t_format *ptr_fc;
	
	fconf.prec = -1;
	fconf.width = -1;
	fconf.flag = 0;
    fconf.opt = '\0';
    ptr_fc = &fconf;
	retval = 1;
	next = ft_next_conv(format, ptr_fc);
	if (fconf.opt == 'c')
		ft_putchar_fd(*next, 1);
	else if (fconf.opt == 's')
		retval = ft_str_formatted(va_arg(*ap, char *), ptr_fc);
	else if (fconf.opt == 'p')
		retval = ft_itoa_formatted((long long) va_arg(*ap, void *), ptr_fc);
	else
		retval = ft_itoa_formatted(va_arg(*ap, long long), ptr_fc);
	while (format != next+1)
        format++;
    return (retval);
}

int ft_prenum_handler(long long *nb, t_format *fconf, char *prenum)
{
	prenum = "";
	if (fconf->opt == 'p' || (ft_tolower(fconf->opt) == 'x' && fconf->flag & FLAG_HASH))
		prenum = "0x";
	else if (nb < 0)
	{
		*nb = - (*nb);
		prenum = "-";
	}
	else if (fconf->flag & FLAG_PLUS)
		prenum = "+";
	else if (fconf->flag & FLAG_SPACE)
		prenum = " ";
	return (ft_strlen(prenum));
}

int ft_str_formatted(char *s, t_format *fconf)
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

void formated_number(long long nb, t_format *fconf, t_fnum *fnum)
{
	fnum->nzeros = 0;
	fnum->nspaces = 0;
	ft_prenum_handler(&nb, fconf, fnum->prenum);
	if (fconf->opt == 'p' || ft_tolower(fconf->opt) == 'x')
	{
		fnum->num = ft_ibasetoa(nb, 16);
		if (fconf->opt == 'X')
		{
			ft_striter(fnum->prenum, ft_toupper);
			ft_striter(fnum->num, ft_toupper);
		}
    }    
	else
		fnum->num = ft_ibasetoa(nb, 10);
	fnum->len = (int) ft_strlen(fnum->num) + ft_strlen(fnum->prenum);
}	

/* '' (left-justified) < '0' (left zeros) < '-' (left spaces)*/
/* '' (no char for positive sign) < ' ' (space for positive sign) < '+' (plus * for positive sign) done */
/* '#' For 'x' and 'X' show '0x/X'. Always present in 'p' done */
/* precision: min number of digits */
/* width: min number of chars */
/* digits_number >= precision >= width */
int ft_itoa_formatted(long long nb, t_format *fconf)
{
	t_fnum fnum;

	formated_number(nb, fconf, &fnum);
	if (fconf->prec > fnum.len)
		fnum.nzeros = fconf->prec - fnum.len;
	if (fconf->width > fnum.len)
		fnum.nspaces = fconf->width - fnum.len - fnum.nzeros;
	if (fconf->flag & FLAG_MINUS)
		ft_putchars_n_fd(' ', 1, fnum.nspaces + fnum.nzeros);
	ft_putstr_fd(fnum.prenum, 1);
	if (fconf->flag & FLAG_ZERO)
		ft_putchars_n_fd('0', 1, fnum.nzeros);
	ft_putstr_fd(fnum.num, 1);
	if (!(fconf->flag & FLAG_MINUS))
		ft_putchars_n_fd(' ', 1, fnum.nspaces);
	return (fnum.len + fnum.nspaces + fnum.nzeros);
}

const char	*ft_next_conv(const char *c, t_format *fconf)
{
	while (*c != '\0')
	{
		if (*c == 'c' || *c == 's' || *c == 'p' || *c == 'd' || *c == 'i'
			|| *c == 'u' || *c == 'x' || *c == 'X')
		{
			fconf->opt = *c;
			return (c);
		}
		else if (*c == '.')
			fconf->prec = ft_atoi(c + 1);
		else if (*c >= '1' && *c <= '9' && fconf->prec < 0)
			fconf->width = ft_atoi(c);
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
