/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:06:41 by vilibert          #+#    #+#             */
/*   Updated: 2024/01/23 15:33:03 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace(char *old_str, char *new_str, int i, int j)
{
	char	*part_1;
	char	*part_2;
	char	*tmp;

	part_1 = ft_substr(old_str, 0, i);
	part_2 = ft_substr(old_str, j, ft_strlen(old_str + j));
	if (!part_1 || !part_2)
		return (free(part_1), free(part_2), NULL);
	if (!new_str)
	{
		tmp = ft_strjoin(part_1, part_2);
		return (free(part_1), free(part_2), tmp);
	}
	tmp = ft_strjoin(part_1, new_str);
	free(part_1);
	if (!tmp)
		return (free(part_2), NULL);
	part_1 = ft_strjoin(tmp, part_2);
	free(part_2);
	free(tmp);
	if (!part_1)
		return (NULL);
	return (part_1);
}
