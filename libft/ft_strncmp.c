/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:07:56 by vilibert          #+#    #+#             */
/*   Updated: 2023/10/17 12:22:28 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				response;

	i = 0;
	response = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		response = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (response == 0)
			i++;
		else
			return (response);
	}
	return (response);
}
