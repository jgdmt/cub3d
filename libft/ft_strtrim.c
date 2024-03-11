/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:26:33 by vicode            #+#    #+#             */
/*   Updated: 2023/10/18 14:14:49 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_scan(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			j++;
		}
		if (s1[i] != set[j])
			break ;
		i++;
	}
	return (i + 1);
}

static int	ft_reverse_scan(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) -1 ;
	while (i >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			j++;
		}
		if (s1[i] != set[j])
			break ;
		i--;
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = ft_scan(s1, set);
	end = ft_reverse_scan(s1, set);
	if (end - start + 1 < 0)
		return (ft_calloc(1, sizeof(char)));
	ptr = ft_substr(s1, start - 1, end - start + 1);
	if (!ptr)
		return (NULL);
	return (ptr);
}
