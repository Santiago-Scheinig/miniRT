/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:13:33 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 22:57:37 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Creates and allocates a pointer to a STRING that includes every character 
 * included in all STRINGS of ARGV.
 * @param argv The main arguments.
 * @param c The character used to joined the STRINGS.
 * @return A pointer to the new joined STRING.
 */
char	*ft_argjoin(char **argv, char c)
{
	char	*str;
	int		i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (argv[++i])
		str_len += ft_strlen(argv[i]);
	str_len += i;
	str = ft_calloc(str_len + 1, sizeof(char));
	i = 0;
	while (argv[++i])
	{
		ft_strlcat(str, argv[i], str_len);
		ft_strlcat(str, &c, str_len);
	}
	return (str);
}
