/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:43:25 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:07:30 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/**
 * Failsafe specific to ft_printf in case of error.
 * - Ends the va_list args and frees text and it's content, returning -1 to
 *   indicate an error ocurred.
 * - Notice that if va_list args is NULL, it still frees text and it's
 *	 content, returning 0 to indicate the free was successfull.
 */
static	int	ft_forcend(va_list args, t_print text)
{
	int	ans;

	ans = -1;
	if (args)
		va_end(args);
	else
		ans = 0;
	if (text.flags)
		free(text.flags);
	if (text.str)
		free(text.str);
	return (ans);
}

/**
 * Creates a new CHAR * with the next arg value as text ready to print.
 * - Using spf, the function assigns to the CHAR * it's expected format.
 */
static	char	*ft_getarg(char spf, va_list args)
{
	void	*str;

	str = NULL;
	if (spf == '%')
		str = ft_chrdup('%');
	else if (spf == 'c')
		str = ft_chrdup(va_arg(args, int));
	else if (spf == 'u')
		str = ft_utoa_base(va_arg(args, unsigned int), "0123456789");
	else if (spf == 'd' || spf == 'i')
		str = ft_itoa(va_arg(args, int));
	else if (spf == 'x' || spf == 'X')
		str = ft_utoa_base(va_arg(args, unsigned int), ft_sethexa(spf));
	else if (spf == 'p')
	{
		str = va_arg(args, void *);
		if (!str)
			return (ft_strdup("(nil)"));
		str = ft_ptrdup(ft_utoa_base((size_t) str, ft_sethexa(spf)), 'p');
	}
	else if (spf == 's')
		str = ft_strdup(va_arg(args, char *));
	if ((!str && spf == 's'))
		return (ft_strdup("(null)"));
	return ((char *) str);
}

/**
 * 
 * Creates and returns a new CHAR * that includes a modified str with the
 * expected parameters indicated on flags.
 * - Verifies specific NULL print formats for specifier 's'.
 * - If the specifier is 's' - 'c' - '%', returns ft_txtwth. Notice that if
 *   specifier is 's' and presicion is true, the str_len of 's' is changed
 *   to flags[6].
 * - If the specifier is 'x' - 'X' - 'p', verifies specific NULL print
 *   formats, returning ft_txtwht with str_len = 0. Otherwise, it returns
 *   ft_hexwth.
 * - If the specifier is 'i' - 'd' - 'u', returns ft_dgtwth.
 */
static	char	*ft_flagstr(char *str, int *flags, int str_len)
{
	if (flags[7] == 's' && flags[6] <= 5 && !ft_strncmp(str, "(null)", 6))
		if (flags[6] != -1)
			flags[6] = 0;
	if (flags[7] == 's' || flags[7] == 'c' || flags[7] == '%')
	{
		if (flags[7] == 's' && flags[6] < str_len && flags[6] != -1)
			str = ft_txtwth(flags, str, flags[6]);
		else
			str = ft_txtwth(flags, str, str_len);
	}
	else if (flags[7] == 'x' || flags[7] == 'X' || flags[7] == 'p')
	{
		if (!ft_strncmp("0", str, 2) && flags[6] == 0)
			str = ft_txtwth(flags, str, 0);
		else
			str = ft_hexwth(flags, str, str_len);
	}
	else
		str = ft_dgtwth(flags, str, str_len);
	return (str);
}

/**
 * Writes in stdout and adds the amount of printed characters to count.
 * - Verifies specific NULL print formats for specifier 'c'.
 * - If the verification turns false, calls ft_flagstr to obtain an str
 *   that meets the expected paramaters indicated on flags.
 */
static	int	ft_printv(t_print text, int *count)
{
	int		zero;

	zero = 1;
	if (text.flags[7] == 'c' && !text.str[0])
	{
		zero = 0;
		if (text.flags[5] > 1)
		{
			free(text.str);
			text.str = ft_calloc(text.flags[5] - 1, sizeof(char *));
			if (!text.str)
				return (-1);
			ft_memset(text.str, ' ', text.flags[5] - 1);
		}
	}
	else
		text.str = ft_flagstr(text.str, text.flags, ft_strlen(text.str));
	if (!text.str)
		return (-1);
	if (!zero && text.flags[0])
		*count += ft_putchar_fd(zero++, 1);
	*count += ft_putstr_fd(text.str, 1);
	if (!zero)
		*count += ft_putchar_fd(zero, 1);
	return (ft_forcend(NULL, text));
}

/**
 * Writes the formatted output to stdout.
 */
int	ft_printf(char const *s, ...)
{
	va_list	args;
	t_print	text;
	int		count;

	count = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			text.flags = ft_flagdescriptor(s + 1);
			if (!text.flags)
				return (ft_forcend(args, text));
			text.str = ft_getarg(text.flags[7], args);
			if (!text.str)
				return (ft_forcend(args, text));
			s = ft_strchr(s + 1, text.flags[7]) + 1;
			if (ft_printv(text, &count) < 0)
				return (ft_forcend(args, text));
		}
		else
			count += ft_putchar_fd(*s++, 1);
	}
	va_end(args);
	return (count);
}
