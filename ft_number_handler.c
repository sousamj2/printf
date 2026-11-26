/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 16:46:23 by marisous          #+#    #+#             */
/*   Updated: 2026/11/26 22:43:18 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_prenum_handler(long long *nb, t_format *fconf, t_fnum *fnum)
{
	fnum->prenum = NULL;
	if (fconf->opt == 'p'
		|| (ft_tolower(fconf->opt) == 'x' && fconf->flag & FLAG_HASH))
		fnum->prenum = ft_strdup("0x");
	else if (*nb < 0)
	{
		*nb = - (*nb);
		fnum->prenum = ft_strdup("-");
	}
	else if (fconf->flag & FLAG_PLUS)
		fnum->prenum = ft_strdup("+");
	else if (fconf->flag & FLAG_SPACE)
		fnum->prenum = ft_strdup(" ");
	if (fnum->prenum == NULL)
		fnum->prenum = "";
	fnum->len_prenum = ft_strlen(fnum->prenum);
	return (fnum->len_prenum);
}

void	formated_number(long long nb, t_format *fconf, t_fnum *fnum)
{
	fnum->nzeros = 0;
	fnum->nspaces = 0;
	ft_prenum_handler(&nb, fconf, fnum);
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
	fnum->len_num = (int) ft_strlen(fnum->num);
}

/* '' (left-justified) < '0' (left zeros) < '-' (left spaces)*/
/* '' (no char for positive sign) < ' ' (space for positive sign) <
   '+' (plus * for positive sign) done */
/* '#' For 'x' and 'X' show '0x/X'. Always present in 'p' done */
/* precision: min number of digits */
/* width: min number of chars */
/* digits_number >= precision >= width */
int	ft_itoa_formatted(long long nb, t_format *fconf)
{
	t_fnum	fnum;

	if (fconf->opt == 'p' && nb == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	formated_number(nb, fconf, &fnum);
	if (fconf->prec + fnum.len_prenum > fnum.len_num)
		fnum.nzeros = fconf->prec - fnum.len_num ;
	if (fconf->width > fnum.len_num)
		fnum.nspaces = fconf->width - fnum.len_num - fnum.nzeros
			- fnum.len_prenum;
	if (!(fconf->flag & FLAG_MINUS))
		ft_putchars_n_fd(' ', 1, fnum.nspaces);
	ft_putstr_fd(fnum.prenum, 1);
	if (fconf->flag & FLAG_ZERO
		|| (fconf->prec + fnum.len_prenum) > fnum.len_num)
		ft_putchars_n_fd('0', 1, fnum.nzeros);
	ft_putstr_fd(fnum.num, 1);
	if (fconf->flag & FLAG_MINUS)
		ft_putchars_n_fd(' ', 1, fnum.nspaces);
	free(fnum.num);
	if (fnum.prenum != NULL && ft_strlen(fnum.prenum) > 0)
		free(fnum.prenum);
	return (fnum.len_num + fnum.nspaces + fnum.nzeros + fnum.len_prenum);
}
