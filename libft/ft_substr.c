/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:49:15 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/24 13:43:55 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;
	size_t	ptr_len;

	if (!s)
		return (0);
	ptr_len = 0;
	while (start < ft_strlen(s) && (ptr_len < len && s[start + ptr_len]))
		ptr_len++;
	ptr = malloc(sizeof(char) * (ptr_len + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (start < ft_strlen(s) && i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
