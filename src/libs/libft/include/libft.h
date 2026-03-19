/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:37:54 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 22:57:54 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "ft_printf.h"
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <limits.h>
# include <unistd.h>

/*--------------------------------------------------------------------------*/
/*----------------------------------STRING----------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Copies size bytes from a CONST STRING src at the end of a STRING des.
 * @param dst The STRING where to copy src.
 * @param src The CONST STRING to copy from.
 * @param size The amount of bytes to be copied from src into des.
 * @return The total lenght of the STRING tried to copy, in this case,
 * the lenght of src.
 * @note - If size >= src_len + 1, it copies all of src into des.
 * @note - Else, it truncates the copy after size - 1 bytes.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * Concatenates size bytes from a CONST STRING src at the end of a STRING des.
 * @param dst The STRING where to concatenate src.
 * @param src The CONST STRING to be concatenated into des.
 * @param size The amount of bytes to be concatenated from src into des.
 * @return The total lenght of the STRING tried to concatenate, in this case,
 * the initial lenght of des plus the lenght of src.
 * @note - If size <= dst_len, it doesn't concatenate.
 * @note - If size >= dst_len + src_len + 1, it concatenates all of src.
 * @note - Else, it truncates the concatenation after size - 1 bytes.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/**
 * Counts the amount of characters on a CONST STRING.
 * @param s The CONST STRING to count characters from.
 * @return An INT with the amount of characters counted.
 * @note This function doesn't count the '\0' character.
 */
size_t	ft_strlen(const char *s);

/**
 * Splits a STRING into an ARRAY of STRINGS, using a divisor character.
 * @param s The STRING to split.
 * @param c The character which divides each word.
 * @return An ARRAY of STRINGS that includes every divided word and is 
 * NULL terminated.
 */
char	**ft_split(char const *s, char c);

/**
 * Splits a STRING into an ARRAY of STRINGS, using a divisor character.
 * @param s The STRING to split.
 * @param c The character which divides each word.
 * @return An ARRAY of STRINGS that includes every divided word and is 
 * NULL terminated.
 * @note This function will ignore any C coincidences that happen to be inside
 * of single and double quotes (as long they open and close).
 */
char	**ft_iq_split(char const *s, char c);

/**
 * Creates and allocates a STRING writen with the UNSIGNED LONG INT 
 * passed as argument, following the specified base.
 * @param n The number to write inside of the STRING.
 * @param base The base in which the number must be found
 * @return A pointer to the new allocated STRING; Or NULL in case of error.
 */
char	*ft_utoa_base(size_t n, const char *base);

/**
 * Searches for the first match of all of a CONST STRING little in a 
 * CONST STRING big for len bytes.
 * @param big The large CONST STRING to find the match.
 * @param small The small CONST STRING to be matched on big.
 * @param len The amount of bytes to search on big.
 * @return A pointer to the CONST STRING where the full first match
 * was found; Or NULL if no match where found or big doesn't exists.
 * @note - The match musst exist in len bytes of big.
 * @note - Returns big if little is empty.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * Creates and allocates a new STRING with len bytes copied from the 
 * CONST STRING starting on the start position.
 * @param s The CONST STRING to copy from.
 * @param start The index of the CONST STRING to start copying from.
 * @param len The amount of bytes to be copied.
 * @return A pointer to a new STRING resultant of the copy.
 * @note - If start > s_len, it returns a pointer to a new STRING 
 * with one '\0' byte allocated.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * Creates and allocates a new STRING with the result of iterate a 
 * FUNCTION on every character of a CONST STRING.
 * @param s The CONST STRING to be iterated.
 * @param f The FUNCTION to be iterated on every character of the
 * CONST STRING.
 * @return A pointer to the new allocated STRING with the results of
 * all the iterations in order; Or NULL in case of error.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * Creates and allocates a new STRING resultant of the trimming of a 
 * CONST STRING set in a CONST STRING s1.
 * @param s1 The CONST STRING to be compared for trimming.
 * @param set The character base to be trimmed.
 * @return A pointer to the new STRING resultant of the trimming.
 * @note - Cuts every match of 'set' from the start of 's1' until a non match.
 * @note - Cuts every match of 'set' from the end of 's1' until a non match.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * Creates and allocates a new STRING with the result of concatenate two
 * other STRINGS.
 * @param s1 The first STRING to be concatenated.
 * @param s2 The second STRING ot be concatenated.
 * @return A pointer to the new allocated STRING, resulted from the 
 * concatenation; Or NULL in case of error.
 * @note If any of the STRING to be concatenated are non-existent, it
 * returns an error.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * Creates and allocates a pointer to a STRING that includes every character 
 * included in all STRINGS of ARGV.
 * @param argv The main arguments.
 * @param c The character used to joined the STRINGS.
 * @return A pointer to the new joined STRING.
 */
char	*ft_argjoin(char **argv, char c);

/**
 * Searches for the last ocurrance of a character on a STRING.
 * @param s The STRING where to find the ocurrance.
 * @param c The character to be found.
 * @return A pointer to a position of the STRING with the last 
 * character ocurrance. If no ocurrance is found, returns NULL. 
 */
char	*ft_strrchr(const char *s, int c);

/**
 * Searches for the first ocurrance of a character on a STRING.
 * @param s The STRING where to find the ocurrance.
 * @param c The character to be found.
 * @return A pointer to a position of the STRING with the first 
 * character ocurrance. If no ocurrance is found, returns NULL. 
 */
char	*ft_strchr(const char *s, int c);

/**
 * Searches for the first ocurrance of a character on a STRING.
 * @param s The STRING where to find the ocurrance.
 * @param c The character to be found.
 * @return A pointer to a position of the STRING with the first 
 * character ocurrance. If no ocurrance is found, returns NULL. 
 * @note This function will ignore any C coincidences that happen 
 * to be inside of single and double quotes (as long they open and close).
 */
char	*ft_iq_strchr(char const *s, char c);

/**
 * Creates and allocates a STRING that includes all the characters of a CONST
 * STRING.
 * @param s The CONST STRING to allocate.
 * @return A pointer to the new allocated STRING.
 */
char	*ft_strdup(const char *s);

/**
 * Creates and allocates a STRING writen with the INT passed as
 * argument.
 * @param n The number to write inside of the STRING.
 * @return A pointer to the STRING.
 */
char	*ft_itoa(int n);

/**
 * Returns a char * with the next line on the file descriptor given.
 */
char	*get_next_line(int fd);

/**
 * Iterates a FUNCTION on every character of a STRING.
 * @param s The STRING to iterate into.
 * @param f The FUNCTION to iterate on every character of the STRING.
 * @note This function modifies the original STRING, doesn't 
 * allocate a new one.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * Compares two CONST STRING for n bytes.
 * @param s1 The first CONST STRING to be compared.
 * @param s2 The second CONST STRING to be compared.
 * @param n The amount of bytes to be compared,
 * @return 0 if the comparation is true; else a positive or negative INT if
 * false.
 * @note The positive or negative value returned if false is the ASCII 
 * difference between the two characters which trigger the false comparation.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * Writes a STRING into a specific file descriptor.
 * @param s The STRING to be printed.
 * @param fd The file descriptor to print into.
 * @return The amount of characters printed.
 */
int		ft_putstr_fd(char *s, int fd);

/**
 * Writes a STRING into a specific file descriptor.
 * @param s The STRING to be printed.
 * @param fd The file descriptor to print into.
 * @return The amount of characters printed.
 * @note After the STRING is printed, it also writes a '\n' on the file
 * descriptor.
 */
int		ft_putendl_fd(char *s, int fd);

/*--------------------------------------------------------------------------*/
/*---------------------------------INTEGERS---------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Finds the first number on a STRING with a decimal base.
 * @param str The string where the base number is saved.
 * @param base The base in which the number must be found.
 * @return The decimal LONG found on STR.
 * @note A number can, but is not forced to, start with any
 * amount of spaces and one sign; but the next character must 
 * be a digit, if not or str doesn't exists, returns 0.
 */
long	ft_atol(const char *nptr);

/**
 * Finds the first number on a STRING with a decimal base.
 * @param str The string where the base number is saved.
 * @param base The base in which the number must be found.
 * @return The decimal INT found on STR.
 * @note A number can, but is not forced to, start with any
 * amount of spaces and one sign; but the next character must 
 * be a digit, if not or str doesn't exists, returns 0.
 */
int		ft_atoi(const char *nptr);

/**
 * Finds the first number on a STRING following the specified base.
 * @param str The string where the base number is saved.
 * @param base The base in which the number must be found.
 * @return The INT found on STR following the BASE.
 * @note If str has characters not included on the base, or str doesn't
 * exists, returns 0.
 */
int		ft_atoi_base(char *str, const char *base);

/**
 * Writes an INT into a specific file descriptor.
 * @param n The INT to be printed.
 * @param fd The file descriptor to print into.
 * @return The amount of characters printed.
 */
int		ft_putnbr_fd(int n, int fd);

/*--------------------------------------------------------------------------*/
/*--------------------------------CHARACTER---------------------------------*/
/*--------------------------------------------------------------------------*/

int		ft_isalpha(int c);

int		ft_isdigit(int c);

int		ft_isalnum(int c);

int		ft_isascii(int c);

int		ft_isprint(int c);

int		ft_toupper(int c);

int		ft_tolower(int c);

/**
 * Writes a character into a specific file descriptor.
 * @param c The character to be printed.
 * @param fd The file descriptor to print into.
 * @return The amount of characters printed.
 */
int		ft_putchar_fd(char c, int fd);

/*--------------------------------------------------------------------------*/
/*----------------------------------MEMORY----------------------------------*/
/*--------------------------------------------------------------------------*/

/**
 * Moves n bytes from a src VOID pointer into a dest VOID pointer.
 * @param dest The VOID pointer where to move bytes into.
 * @param src The VOID pointer where to move bytes from.
 * @param n The amount of bytes to be moved.
 * @return The VOID pointer to dest.
 * @note This function modifies the dest VOID pointer and, additionally,
 * checks if the memory position of src is close to dest to avoid loosing
 * information during the movement.
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * Copies n bytes from a src VOID pointer into a dest VOID pointer.
 * @param dest The VOID pointer where to copy bytes into.
 * @param src The VOID pointer where to copy bytes from.
 * @param n The amount of bytes to be copied.
 * @return The VOID pointer to dest.
 * @note This function modifies the dest VOID pointer.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * Searches for an INT value inside of a VOID pointer for n bytes.
 * @param s The VOID pointer where to search the INT.
 * @param int The int to be searched.
 * @param n The amount of bytes to search inside of the pointer.
 * @return A VOID pointer to the first match; or NULL if no coincidence 
 * is found.
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * Sets n bytes of a VOID pointer with a specified INT.
 * @param s The VOID pointer to set bytes into.
 * @param c The INT value to be set on each byte.
 * @param n The amount of bytes to be set on the VOID pointer.
 */
void	*ft_memset(void *s, int c, size_t n);

/**
 * Allocates NMEMB * SIZE bytes of memory and sets them to '\0'.
 * @param nmemb The amount of memory bytes to allocate.
 * @param size The size of each memory bytes.
 * @return The void pointer allocated.
 */
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * Erases the data in the n bytes of the memory starting at the location
 * pointed to by s, by writing zeros (bytes containing '\0') to that area.
 * @param s The pointer location where to rewrite.
 * @param n The amount of bytes to rewrite.
 */
void	ft_bzero(void *s, size_t n);

/**
 * Compares two VOID pointers for n bytes.
 * @param s1 The first VOID pointer to be compared.
 * @param s2 The second VOID pointer to be compared.
 * @param n The amount of bytes to be compared.
 * @return 0 if the comparation is true; else a positive or negative INT if
 * false.
 * @note The positive or negative value returned if false is the ASCII 
 * difference between the two characters which trigger the false comparation.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * Frees an ARRAY of STRINGS, usually allocated by ft_split().
 * @param split The ARRAY of STRINGS to free.
 */
void	*ft_split_free(char **split);

/*--------------------------------------------------------------------------*/
/*----------------------------------S_LIST----------------------------------*/
/*--------------------------------------------------------------------------*/

typedef struct s_list
{
	void			*content;
	void			**vectors;
	struct s_list	*next;
}	t_list;

/**
 * Reads and saves a file until EOF, specified by a file descriptor and 
 * dividing it by lines.
 * @param lines The LIST HEAD where to create new nodes for every line read.
 * @param fd The file descriptor to read from.
 * @return The amount of lines read or -1 in case of error.
 * @note A line that is just conformed by a single '\n' character isn't saved
 * and doesn't sum for the amount of lines read.
 */
int		ft_read_file(t_list **lines, int fd);

/**
 * Creates and allocates a new LIST result of iterating a FUNCTION on every
 * content of the original LIST.
 * @param lst The starting node to start iterating.
 * @param f The FUNCTION to iterate on every content.
 * @param del The FUNCTION used to free each content in case of error.
 * @return A pointer to the start of the new allocated LIST; or NULL in case
 * of error.
 * @note If any node creation fails, frees every other previous iteration
 * using the del FUNCTION on every content. Usually being free().
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * Creates and allocates a new LIST node.
 * @param content A pointer to the content to be included inside of the new
 * node.
 * @return A pointer to the new LIST node; or NULL in case of error.
 * @note The next node inside of the LIST node is set to NULL.
 */
t_list	*ft_lstnew(void *content);

/**
 * Searches for a pointer to the last LIST node to be found.
 * @param lst The starting node.
 * @return A pointer to the last LIST node.
 * @note If the starting node doesn't exists, returns NULL.
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * Frees every node included on the LIST HEAD. 
 * @param lst The LIST HEAD to free.
 * @param del The function used to free each node.
 * @note In general, the del function should be free().
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * Frees the content of a NODE. then frees the NODE.
 * @param lst The LIST node to free.
 * @param del The function used to free the content.
 * @note In general, the del function should be free().
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * Iterates a FUNCTION on every content of every LIST following the first one.
 * @param lst The starting node to start iterating.
 * @param f The FUNCTION to iterate on every content.
 */
void	ft_lstiter(t_list *lst, void (f)(void *));

/**
 * Adds a LIST node at the start of a LIST HEAD.
 * @param lst The LIST HEAD where to add the new node.
 * @param new The new LIST node to add.
 * @note The previous node at the start of the LIST HEAD is set
 * as the next node of the new LIST HEAD.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * Adds a LIST node at the end of a LIST HEAD.
 * @param lst The LIST HEAD where to add the new node.
 * @param new The new LIST node to add.
 * @note If the LIST HEAD is empty, sets the new LIST node at the start
 * of it.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * Counts the amount of node included on a LIST.
 * @param lst The starting node where to start counting.
 * @return An int with the amount of nodes inside of the LIST.
 */
int		ft_lstsize(t_list *lst);

#endif
