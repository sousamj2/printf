/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 11:12:14 by marisous          #+#    #+#             */
/*   Updated: 2026/11/27 00:08:35 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#include <printf.h>

int	main(void)
{
	/* char	*str; */
	int		aaaa;
	int		b;

	/* str = "test"; */
	/* b = ft_printf("Test %% [%p] [%p] [%c]\n", (void*)ULONG_MAX, str,'0' +256); */
	/* aaaa = printf("Test %% [%p] [%p] [%c]\n", (void*)ULONG_MAX, str,'0' +256); */
	b = ft_printf("Test %% [%p]\n", ULONG_MAX);
	aaaa = printf("Test %% [%p]\n", ULONG_MAX);
	/* b = ft_printf("Test %% [%p]\n", -ULONG_MAX); */
	/* aaaa = printf("Test %% [%p]\n", -ULONG_MAX); */
	/* b = ft_printf("Test %% [%x]\n", LONG_MIN); */
	/* aaaa = printf("Test %% [%x]\n", LONG_MIN); */
	/* b = ft_printf("Test %% [%X]\n", LONG_MIN); */
	/* aaaa = printf("Test %% [%X]\n", LONG_MIN); */
	/* b = ft_printf("Test %% [%X]\n", ULONG_MAX); */
	/* aaaa = printf("Test %% [%X]\n", ULONG_MAX); */
	printf("%d %d\n", aaaa, b);
	return (0);
}
