/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 11:37:44 by marisous          #+#    #+#             */
/*   Updated: 2026/11/26 22:50:56 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

/**
 * @brief Bitmask flags for printf conversion specifiers.
 *
 * Each enumerator represents one flag character recognised in a format
 * string and is stored as a single bit so that multiple flags can be
 * combined with bitwise OR in a single @c int field.
 *
 * @var FLAG_MINUS  @c '-' — left-justify the output within the field width.
 * @var FLAG_ZERO   @c '0' — pad the field with leading zeros instead of spaces.
 * @var FLAG_HASH   @c '#' — prefix octal with @c 0, hex with @c 0x / @c 0X.
 * @var FLAG_SPACE  @c ' ' — prefix a positive number with a space.
 * @var FLAG_PLUS   @c '+' — always show the sign (@c + or @c -) for numbers.
 */
enum e_flags
{
	FLAG_MINUS = 1u << 0,
	FLAG_ZERO = 1u << 1,
	FLAG_HASH = 1u << 2,
	FLAG_SPACE = 1u << 3,
	FLAG_PLUS = 1u << 4
};

/**
 * @brief Parsed representation of a single printf format specifier.
 *
 * Filled in by ft_next_conv() after scanning the substring that follows
 * a @c % character.  Every field has an explicit "not set" sentinel so
 * that callers can distinguish an absent modifier from a zero value.
 *
 * @var t_format::prec   Precision value (@c -1 when no precision was given).
 * @var t_format::width  Minimum field width (@c -1 when not specified).
 * @var t_format::flag   Bitwise OR of zero or more @c e_flags values.
 * @var t_format::opt    The conversion specifier character
 *                       (@c c, @c s, @c p, @c d, @c i, @c u, @c x, @c X).
 */
typedef struct s_format
{
	int		prec;
	int		width;
	int		flag;
	char	opt;
}	t_format;

/**
 * @brief Intermediate buffer used while rendering a formatted number.
 *
 * Populated by formated_number() and ft_prenum_handler() before the
 * final output is written to the file descriptor.
 *
 * @var t_fnum::prenum      Heap-allocated prefix string (@c "-", @c "+",
 *                          @c " ", @c "0x", or @c "0X"), or @c "" when no
 *                          prefix is needed.
 * @var t_fnum::num         Heap-allocated string of the absolute numeric
 *                          digits (base-10 or base-16).
 * @var t_fnum::nzeros      Number of leading zeros required by the precision.
 * @var t_fnum::nspaces     Number of padding spaces required by the width.
 * @var t_fnum::len_num     Cached @c ft_strlen of @c num.
 * @var t_fnum::len_prenum  Cached @c ft_strlen of @c prenum.
 */
typedef struct s_fnum
{
	char	*prenum;
	char	*num;
	int		nzeros;
	int		nspaces;
	int		len_num;
	int		len_prenum;
}	t_fnum;

/**
 * @brief Converts a signed integer to a heap-allocated string in any base.
 *
 * Handles negative values by prepending a @c '-' sign.  The returned
 * pointer is always the beginning of the allocation (not an interior
 * pointer), so it can be passed directly to @c free().
 *
 * @param n      The integer to convert.
 * @param n_base The numeric base (e.g. 10 for decimal, 16 for hexadecimal).
 * @return Pointer to a null-terminated, heap-allocated string, or @c NULL
 *         if the allocation fails.
 */
char	*ft_ibasetoa(long long n, int n_base);

/**
 * @brief Applies a character-mapping function to every byte of a string.
 *
 * Iterates over @p s in place, replacing each character with the return
 * value of @p f (cast to @c char).  The function receives each character
 * as @c unsigned char to avoid undefined behaviour with standard @c ctype
 * functions.
 *
 * @param s Pointer to the null-terminated string to transform (modified
 *          in place).
 * @param f Pointer to a function that maps one character to another
 *          (e.g. @c ft_toupper, @c ft_tolower).
 */
void	ft_striter(char *s, int (*f)(int));

/**
 * @brief Writes a character to a file descriptor @p n times.
 *
 * Uses @c ft_putchar_fd() internally for each repetition.  Writes nothing
 * when @p n is zero or negative.
 *
 * @param c  The character to repeat.
 * @param fd The file descriptor to write to.
 * @param n  Number of times to write @p c.
 */
void	ft_putchars_n_fd(const char c, int fd, int n);

/**
 * @brief Writes at most @p n bytes of a string to a file descriptor.
 *
 * Stops early if the null terminator is reached before @p n characters
 * have been written.
 *
 * @param s  Pointer to the string to write.
 * @param fd The file descriptor to write to.
 * @param n  Maximum number of characters to write.
 */
void	ft_putstr_fd_n(const char *s, int fd, int n);

/**
 * @brief Populates the prefix fields of a t_fnum for a numeric conversion.
 *
 * Determines and heap-allocates the appropriate prefix string based on the
 * conversion specifier and active flags:
 * - @c 'p' or @c 'x'/'X' with @c FLAG_HASH → @c "0x" (or @c "0X").
 * - Negative @c 'd' value → @c "-" (and negates @p *nb so the caller
 *   works with the absolute value).
 * - @c FLAG_PLUS active → @c "+".
 * - @c FLAG_SPACE active → @c " ".
 * - Otherwise sets @c fnum->prenum to the empty string @c "".
 *
 * @param nb    Pointer to the value being formatted; negated in place for
 *              negative @c 'd' conversions.
 * @param fconf Pointer to the parsed format specifier.
 * @param fnum  Pointer to the t_fnum structure whose @c prenum and
 *              @c len_prenum fields are filled in.
 * @return Length of the prefix string written to @c fnum->prenum.
 */
int		ft_prenum_handler(long long *nb, t_format *fconf, t_fnum *fnum);

/**
 * @brief Builds the numeric string and prefix for a formatted output.
 *
 * Calls ft_prenum_handler() to set the sign/prefix, then converts the
 * absolute value to base 16 (for @c p, @c x, @c X) or base 10 (for all
 * other numeric specifiers) using ft_ibasetoa().  For @c 'X' the prefix
 * and digit string are both upper-cased in place via ft_striter().
 *
 * @param nb    The value to format.
 * @param fconf Pointer to the parsed format specifier.
 * @param fnum  Pointer to the t_fnum structure that receives the results;
 *              @c num and @c len_num are set by this function.
 */
void	formated_number(long long nb, t_format *fconf, t_fnum *fnum);

/**
 * @brief Writes a formatted integer (or pointer) to stdout.
 *
 * Applies precision (minimum digits), field width, left/right justification,
 * zero-padding, prefix, and sign rules as described by @p fconf.  Special
 * case: a null pointer (@c 'p' with value 0) outputs the literal @c "(nil)".
 * Frees the heap buffers inside @p fnum before returning.
 *
 * @param nb    The value to format; for @c 'p' and unsigned types it is
 *              cast at the call site before being passed as @c long long.
 * @param fconf Pointer to the parsed format specifier (precision, width,
 *              flags, and conversion option).
 * @return Total number of characters written to stdout.
 */
int		ft_itoa_formatted(long long nb, t_format *fconf);

/**
 * @brief Writes a single formatted string argument to stdout.
 *
 * Applies precision (maximum characters printed) and field width with
 * left/right justification.  A @c NULL pointer is treated as the string
 * @c "(null)".
 *
 * @param s     The string to print (may be @c NULL).
 * @param fconf Pointer to the parsed format specifier (precision, width,
 *              flags).
 * @return Total number of characters written to stdout.
 */
int		ft_str_formatted(char *s, t_format *fconf);

/**
 * @brief Writes a single formatted character argument to stdout.
 *
 * Outputs @p c via @c ft_putchar_fd() to file descriptor 1.  Width and
 * flag modifiers are not applied to character conversions in this
 * implementation.
 *
 * @param c The character value obtained from the variadic argument list.
 * @return Always returns 1 (one character written).
 */
int		ft_char_formatted(int c);

/**
 * @brief Scans a format string past @c % to find and parse one conversion.
 *
 * Starting at @p format (which points at the @c % character), advances
 * through flag characters (@c -, @c 0, @c #, @c +, @c space), an optional
 * field-width digit sequence, an optional @c .precision, and finally the
 * conversion specifier letter.  All parsed modifiers are written into
 * @p fconf.
 *
 * @param format Pointer to the @c % that opens the conversion specifier.
 * @param fconf  Pointer to a t_format structure to fill in; must be
 *               zero-initialised (prec = width = -1, flag = 0) by the
 *               caller before the first call.
 * @return Pointer to the conversion specifier character inside @p format,
 *         or @c NULL if the end of the string is reached without finding
 *         one.
 */
char	*ft_next_conv(char *format, t_format *fconf);

/**
 * @brief Dispatches a single @c % conversion to the appropriate formatter.
 *
 * Called by ft_printf() whenever a @c % (other than @c %%) is encountered.
 * Initialises a t_format, calls ft_next_conv() to parse the specifier,
 * then dispatches to ft_char_formatted(), ft_str_formatted(), or
 * ft_itoa_formatted() based on the conversion option.  The return value
 * of each formatter is added (minus one, because the caller also increments
 * @p *retval by one) to @p *retval.
 *
 * @param format Pointer to the @c % character in the original format string.
 * @param ap     Pointer to the variadic argument list maintained by
 *               ft_printf().
 * @param retval Pointer to the running character count; updated in place.
 * @return Number of characters in @p format consumed (i.e., the offset
 *         from @p format to the conversion specifier character), so that
 *         the caller can advance its cursor correctly.
 */
int		ft_handle_vargs(char *format, va_list *ap, int *retval);

/**
 * @brief Minimal re-implementation of the standard printf(3) function.
 *
 * Iterates over @p format one character at a time:
 * - Literal characters are written directly to stdout.
 * - @c %% is collapsed to a single @c % character.
 * - Any other @c % sequence is handled by ft_handle_vargs(), which
 *   parses the full specifier, consumes the matching variadic argument,
 *   and writes the formatted result to stdout.
 *
 * Supported conversion specifiers: @c c, @c s, @c p, @c d, @c i,
 * @c u, @c x, @c X.
 *
 * Supported flags (bonus): @c -, @c 0, @c #, @c +, @c (space).
 *
 * @param format Null-terminated format string following the same
 *               @c %[flags][width][.precision]specifier grammar as the
 *               standard printf(3).
 * @param ...    Variadic arguments matching the conversion specifiers in
 *               @p format.
 * @return Total number of characters written to stdout, or a negative
 *         value on error (not currently implemented; errors from underlying
 *         @c write calls are not propagated).
 */
int		ft_printf(const char *format, ...);
#endif
