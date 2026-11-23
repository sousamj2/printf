/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:37:44 by marisous          #+#    #+#             */
/*   Updated: 2026/11/23 22:22:13 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

enum e_flags
{
    FLAG_MINUS = 1u << 0,
    FLAG_ZERO  = 1u << 1,
    FLAG_HASH  = 1u << 2,
    FLAG_SPACE = 1u << 3,
    FLAG_PLUS  = 1u << 4
};

typedef struct s_format {
	int prec;
	int width;
	int flag;
	char opt;
} t_format;

typedef struct s_fnum {
	char	*prenum;
	char	*num;
	int		nzeros;
	int		nspaces;
	int		len;
} t_fnum;

char *ft_ibasetoa(long long n, int n_base);
void ft_striter(char *s, void (*f)(char *));
void ft_putchars_n_fd(const char c, int fd, int n);
int ft_itoa_formatted(long long nb, t_format *fconf);
void formated_number (long long nb, t_format *fconf, t_fnum *fnum);
int ft_str_formatted(char *s, t_format *fconf);
void ft_prenum_handler(long long *nb, t_format *fconf, char *prenum);
void ft_handle_vargs(const char *format, va_list ap);
int ft_prinft(const char *format, ...);
char	*ft_next_conv(const char *format);

#endif
