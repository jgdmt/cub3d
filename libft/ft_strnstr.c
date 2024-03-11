/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:51:18 by vilibert          #+#    #+#             */
/*   Updated: 2023/11/07 14:36:05 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)hay);
	i = 0;
	if ((!hay || !needle) && len == 0)
		return (0);
	while (hay[i] && i < len)
	{
		j = 0;
		while (hay[i + j] && needle[j] && \
			hay[i + j] == needle[j] && i + j < len)
			j++;
		if (!needle[j])
			return ((char *)hay + i);
		i++;
	}
	return (0);
}
