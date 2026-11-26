/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 11:12:14 by marisous          #+#    #+#             */
/*   Updated: 2026/11/26 17:05:03 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <printf.h>

int	main(void)
{
	char	*str;
	int		a;
	int		b;

	str = "test";
	a = printf("Test %% %% [%11.5s] [%#10.2x] [%p]\n", str, 100, str);
	b = ft_printf("Test %% %% [%11.5s] [%#10.2x] [%p]\n", str, 100, str);
	printf("%d %d\n", a, b);
	return (0);
}
