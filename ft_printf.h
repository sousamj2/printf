/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:37:44 by marisous          #+#    #+#             */
/*   Updated: 2026/11/26 16:21:09 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

enum e_flags
{
	FLAG_MINUS = 1u << 0,
	FLAG_ZERO = 1u << 1,
	FLAG_HASH = 1u << 2,
	FLAG_SPACE = 1u << 3,
	FLAG_PLUS = 1u << 4
};

typedef struct s_format
{
	int		prec;
	int		width;
	int		flag;
	char	opt;
}	t_format;

typedef struct s_fnum
{
	char	*prenum;
	char	*num;
	int		nzeros;
	int		nspaces;
	int		len_num;
	int		len_prenum;
}	t_fnum;

char	*ft_ibasetoa(long long n, int n_base);
void	ft_striter(char *s, int (*f)(int));
void	ft_putchars_n_fd(const char c, int fd, int n);
int		ft_itoa_formatted(long long nb, t_format *fconf);
void	formated_number(long long nb, t_format *fconf, t_fnum *fnum);
int		ft_str_formatted(char *s, t_format *fconf);
int		ft_prenum_handler(long long *nb, t_format *fconf, t_fnum *fnum);
int		ft_handle_vargs(char *format, va_list *ap, int *retval);
int		ft_printf(const char *format, ...);
char	*ft_next_conv(char *format, t_format *fconf);
void	ft_putchars_n_fd(const char c, int fd, int n);
void	ft_putstr_fd_n(const char *s, int fd, int n);
#endif
