/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 11:12:14 by marisous          #+#    #+#             */
/*   Updated: 2026/11/26 14:42:11 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
#include <stdio.h>
#include <printf.h>

int main(void)
{
	char * str = "test";

    int a =    printf("Test %% %% [%11.5s] [%#10.2x] [%p]\n",str, 100, str);
    int b = ft_prinft("Test %% %% [%11.5s] [%#10.2x] [%p]\n",str, 100, str);
    /* int a =    printf("Test %% %% [%11.5s]\n","test"); */
    /* int b = ft_prinft("Test %% %% [%11.5s]\n","test"); */

	printf("%d %d\n", a, b);
    
    return (0);
}
