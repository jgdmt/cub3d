/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:04:21 by vilibert          #+#    #+#             */
/*   Updated: 2023/10/18 14:14:39 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_isspaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (&str[i]);
}

int	ft_atoi(const char *str)
{
	int			neg;
	long int	res;
	long int	last;

	str = ft_isspaces(str);
	neg = 1;
	res = 0;
	last = 0;
	if (*str == '-')
		neg = -neg;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		if (last > res && neg == 1)
			return (-1);
		else if (last > res && neg == 0)
			return (0);
		str++;
		last = res;
	}
	return (res * neg);
}
