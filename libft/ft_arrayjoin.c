/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:04:50 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/24 13:38:06 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrayjoin(char **old, char **new, int size_new)
{
	char	**new_array;
	int		i;
	int		j;

	if (!old)
		return (NULL);
	new_array = malloc((ft_strslen(old) + size_new + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (old[i])
	{
		new_array[i] = old[i];
		i++;
	}
	j = 0;
	while (j < size_new)
	{
		new_array[i] = new[j];
		i++;
		j++;
	}
	new_array[i] = 0;
	return (new_array);
}
