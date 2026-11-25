/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 11:12:14 by marisous          #+#    #+#             */
/*   Updated: 2026/11/25 16:08:55 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
#include <stdio.h>
#include <printf.h>

int main(void)
{
    int a =    printf("Test %% %% [%11.5s] [%#12.11x]\n","test", 1000);
    int b = ft_prinft("Test %% %% [%11.5s] [%#12.11x]\n","test", 1000);
    /* int a =    printf("Test %% %% [%11.5s]\n","test"); */
    /* int b = ft_prinft("Test %% %% [%11.5s]\n","test"); */

	printf("%d %d\n", a, b);
    
    return (0);
}
