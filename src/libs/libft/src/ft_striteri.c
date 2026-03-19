/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:53:51 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 21:52:48 by sscheini         ###   ########.fr       */
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
