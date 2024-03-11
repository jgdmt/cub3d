/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:28:18 by vicode            #+#    #+#             */
/*   Updated: 2024/01/24 13:42:05 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fillboard(int *board, int size)
{
	int	i;

	i = 0;
	if (board == 0)
		return ;
	while (i < size)
		board[i++] = 0;
}

static void	ft_free(char **strs, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(strs[i++]);
}

static int	ft_count(const char *str, char c)
{
	int	size;

	size = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str && *str != c)
			size++;
		while (*str != c && *str)
			str++;
	}
	return (size);
}

static int	ft_make(char const *s, char c, char **strs, int *ijkl)
{
	char	*word;

	while (s[ijkl[0]])
	{
		ijkl[1] = ijkl[0];
		while (s[ijkl[0]] != c && s[ijkl[0]])
			ijkl[0]++;
		word = malloc((ijkl[0] - ijkl[1] + 1) * sizeof(char));
		if (word == NULL)
		{
			ft_free(strs, ijkl[3]);
			return (0);
		}
		ijkl[2] = 0;
		while (ijkl[1] < ijkl[0])
			word[ijkl[2]++] = s[ijkl[1]++];
		word[ijkl[2]] = '\0';
		while (s[ijkl[0]] == c && s[ijkl[0]])
			ijkl[0]++;
		if (word[0] != '\0')
			strs[ijkl[3]++] = word;
		else
			free(word);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		ijkl[4];

	if (s == NULL)
		return (0);
	strs = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (strs == NULL)
		return (0);
	ft_fillboard(ijkl, 4);
	if (ft_make(s, c, strs, ijkl) == 0)
	{
		free(strs);
		return (0);
	}
	strs[ijkl[3]] = 0;
	return (strs);
}
