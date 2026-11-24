/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ibasetoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 19:17:11 by marisous          #+#    #+#             */
/*   Updated: 2026/11/24 16:25:13 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static char	*ft_ibasetoa_mem(long long *n_long, int *negative, size_t *nchars, int n_base);

static long	long ft_get_max_power_base(size_t ndigits, long long long_n, int n_base);

static char	*ft_ibasetoa_mem(long long *n_long, int *negative, size_t *nchars, int n_base)
{
	char	*retval;
	long	n_longcopy;

	*negative = 0;
	*nchars = 1;
	if (*n_long <= 0)
		(*nchars)++;
	if (*n_long < 0)
	{
		*n_long *= -1;
		*negative = 1;
	}
	n_longcopy = *n_long;
	while (n_longcopy > 0)
	{
		(*nchars)++;
		n_longcopy /= n_base;
	}
	retval = ft_calloc(*nchars, sizeof(char));
	if (!retval)
		return (NULL);
	if (*negative)
		*(retval) = '-';
	return (retval);
}

static long long	ft_get_max_power_base(size_t ndigits, long long long_n, int n_base)
{
	long long	power;
	size_t		ichar;

	ichar = 0;
	power = 1;
	while (ichar < ndigits)
	{
		power *= n_base;
		ichar++;
	}
	if (long_n / power == 0)
		power /= n_base;
	return (power);
}

char	*ft_ibasetoa(long long n, int n_base)
{
	char	*retval;
	int		neg;
	size_t	nchars;
	long long	n_long;
	long long	power;

	n_long = n;
	retval = ft_ibasetoa_mem(&n_long, &neg, &nchars, n_base);
	if (retval == NULL)
		return (NULL);
	power = ft_get_max_power_base(nchars - neg - 1, n_long, n_base);
	if (neg)
		retval++;
	while (power > 0)
	{
		*retval = '0' + n_long / power;
		if (*retval > '9')
			*retval += 39;
		n_long %= power;
		power /= n_base;
		retval++;
	}
	retval -= (nchars - 1);
	return (retval);
}
