/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoudema <jgoudema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:01:24 by jgoudema          #+#    #+#             */
/*   Updated: 2024/03/15 18:47:51 by jgoudema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	split_is_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	split_count(char *str, char *sep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && split_is_sep(str[i], sep))
			i++;
		if (str[i])
			len++;
		while (str[i] && !split_is_sep(str[i], sep))
			i++;
	}
	return (len);
}

static int	split_size(char *str, char *sep)
{
	int	i;

	i = 0;
	while (str[i] && !split_is_sep(str[i], sep))
		i++;
	return (i);
}

void	split_free(char **array, int len)
{
	int	i;

	i = 0;
	while (array[i] || (i != -1 && i < len))
		free(array[i++]);
	free(array);
}

char	**ft_modif_split(char *str, char *sep)
{
	char	**array;
	char	*word;
	int		i;

	array = malloc(sizeof(char *) * (split_count(str, sep) + 1));
	i = 0;
	if (!array)
		return (NULL);
	while (*str)
	{
		while (*str && split_is_sep(*str, sep))
			str++;
		if (!(*str))
			break ;
		word = ft_substr(str, 0, split_size(str, sep));
		if (!word)
			return (split_free(array, i), NULL);
		while (*str && !split_is_sep(*str, sep))
			str++;
		array[i++] = word;
	}
	array[i] = NULL;
	return (array);
}
