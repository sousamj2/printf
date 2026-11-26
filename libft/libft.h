/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 15:36:15 by marisous          #+#    #+#             */
/*   Updated: 2026/11/26 16:11:27 by marisous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

/**
 * @brief Tests for a digit (0 through 9).
 *
 * @param c Character to test.
 * @return Non-zero if the character is a digit, 0 otherwise.
 */
int				ft_isdigit(int c);

/**
 * @brief Compares at most the first n bytes of strings s1 and s2.
 *
 * @param s1 First string to compare.
 * @param s2 Second string to compare.
 * @param n Maximum number of bytes to compare.
 * @return Difference s1[i] - s2[i] at the first mismatch, or 0 if identical.
 */
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Allocates and returns a string representing the integer received as
 * an argument. Negative numbers are handled.
 *
 * @param n Integer to convert.
 * @return String representing the integer, or NULL if allocation fails.
 */
char			*ft_itoa(int n);

/**
 * @brief Outputs the character 'c' to the given file descriptor.
 *
 * @param c Character to output.
 * @param fd File descriptor on which to write.
 */
void			ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string 's' to the given file descriptor.
 *
 * @param s String to output.
 * @param fd File descriptor on which to write.
 */
void			ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs the integer 'n' to the given file descriptor.
 *
 * @param n Integer to output.
 * @param fd File descriptor on which to write.
 */
void			ft_putnbr_fd(int n, int fd);

/**
 * @brief Locates the first occurrence of character c in the string s.
 *
 * @param s String to search.
 * @param c Character to locate (converted to char).
 * @return Pointer to the matched character or NULL if not found.
 */
char			*ft_strchr(const char *s, int c);

/**
 * @brief Calculates the length of the string s.
 *
 * @param s Null-terminated string to measure.
 * @return The number of characters preceding the terminating null character.
 */
size_t			ft_strlen(const char *s);

/**
 * @brief Locates the first occurrence of the null-terminated string
 * little in the string big, where not more than len characters are searched.
 *
 * @param big String to be searched.
 * @param little Substring to find.
 * @param len Maximum number of characters to search within big.
 * @return Pointer to the start of the substring, big if little is empty, or
 * NULL if not found.
 */
char			*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief Converts a lower-case letter to the corresponding upper-case letter.
 *
 * @param c Character to convert.
 * @return Converted uppercase character, or c unchanged if not lowercase.
 */
int				ft_toupper(int c);

/**
 * @brief Converts an upper-case letter to the corresponding lower-case letter.
 *
 * @param c Character to convert.
 * @return Converted lowercase character, or c unchanged if not uppercase.
 */
int				ft_tolower(int c);

/**
 * @brief Applies the function 'f' on each character of the string passed as
 * argument, passing its index as first argument. Each character is passed by
 * address to 'f' to be modified if necessary.
 *
 * @param s String on which to iterate.
 * @param f Function to apply to each character of 's' and its index.
 */
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief Converts the initial portion of the string pointed to by nptr to int.
 *
 * @param nptr String representation of an integral number.
 * @return The converted integer value.
 */
int				ft_atoi(const char *nptr);

/**
 * @brief Allocates memory for an array of n elements of size bytes each and
 * initializes all bytes to zero.
 *
 * @param n Number of elements.
 * @param size Size in bytes of each element.
 * @return Pointer to allocated zeroed memory, or NULL if allocation fails.
 */
void			*ft_calloc(size_t n, size_t size);

/**
 * @brief Fills the first n bytes of the memory area pointed to by s with
 * the constant byte c.
 *
 * @param s Pointer to the block of memory to fill.
 * @param c Byte value to set (converted to unsigned char).
 * @param n Number of bytes to be set.
 * @return Pointer to the memory area s.
 */
void			*ft_memset(void *s, int c, size_t n);

/**
 * @brief Erases the data in the n bytes of the memory starting at the location
 * pointed to by s, by writing zeroes ('\0') to that area.
 *
 * @param s Pointer to the block of memory to clear.
 * @param n Number of bytes to set to zero.
 */
void			ft_bzero(void *s, size_t n);

/**
 * @brief Duplicates the string s by allocating sufficient memory with malloc.
 *
 * @param s String to duplicate.
 * @return Pointer to the duplicate string, or NULL if allocation fails.
 */
char			*ft_strdup(const char *s);

/**
 * @brief Copies up to size - 1 characters from the null-terminated string src
 * to dst, null-terminating the result if size is not zero.
 *
 * @param dst Destination buffer.
 * @param src Source string to copy.
 * @param size Total size of the destination buffer.
 * @return Total length of the string attempted to be created (length of src).
 */
size_t			ft_strlcpy(char *dst, const char *src, size_t size);

#endif
