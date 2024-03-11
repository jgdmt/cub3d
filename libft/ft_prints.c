/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:12:12 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/19 14:49:26 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int fd, char c, int *length)
{
	int	status;

	status = write(fd, &c, 1);
	if (status == 1)
		*(length) += 1;
	return (status);
}

int	ft_putstr(int fd, char *str, int *length)
{
	int	status;

	if (str == NULL)
		return (ft_putstr(fd, "(null)", length));
	while (*str)
	{
		status = ft_putchar(fd, *str++, length);
		if (status != 1)
			return (status);
	}
	return (status);
}

int	ft_putnbr(int fd, int n, int *length)
{
	char	*nbr;
	int		status;

	nbr = ft_itoa(n);
	status = ft_putstr(fd, nbr, length);
	free(nbr);
	return (status);
}

int	ft_putunbr(int fd, unsigned int n, int *length)
{
	char	*nbr;
	int		status;

	nbr = ft_uitoa(n);
	status = ft_putstr(fd, nbr, length);
	free(nbr);
	return (status);
}
