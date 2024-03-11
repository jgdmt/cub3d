/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:36:59 by vicode            #+#    #+#             */
/*   Updated: 2024/01/24 13:41:05 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n, int *neg)
{
	int	i;

	i = 0;
	*neg = 1;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		*neg *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(str) - 1;
	while (i <= ((len - 1) / 2))
	{
		tmp = str[len - i];
		str[len - i] = str[i];
		str[i] = tmp;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		neg;

	i = 0;
	neg = 0;
	str = malloc(sizeof(char) * (ft_nbrlen(n, &neg) + 1));
	if (!str)
		return (NULL);
	if (n == 0)
		str[i++] = '0';
	while (n != 0)
	{
		str[i++] = ((n % 10) * neg) + '0';
		n /= 10;
	}
	if (neg == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}

static int	ft_unbrlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_unbrlen(n) + 1));
	if (!str)
		return (NULL);
	if (n == 0)
		str[i++] = '0';
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	str[i] = '\0';
	return (ft_strrev(str));
}
