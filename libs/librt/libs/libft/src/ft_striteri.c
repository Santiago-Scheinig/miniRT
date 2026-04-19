/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:53:51 by sscheini          #+#    #+#             */
/*   Updated: 2026/04/01 17:36:18 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Iterates a FUNCTION on every character of a STRING.
 * @param s The STRING to iterate into.
 * @param f The FUNCTION to iterate on every character of the STRING.
 * @note This function modifies the original STRING, doesn't 
 * allocate a new one.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int		i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
