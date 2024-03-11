/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilibert <vilibert@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:41:58 by vilibert          #+#    #+#             */
/*   Updated: 2023/12/07 12:49:54 by vilibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_error(char *str, char *str2)
{
	free(str);
	if (!str2)
		return (NULL);
	free(str2);
	return (NULL);
}

static char	*get_line(char *buff)
{
	char	*str;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i--] = 0;
	while (i >= 0)
	{
		str[i] = buff[i];
		i--;
	}
	return (str);
}

static char	*get_next_buff(char *buff)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
		return (ft_error(buff, 0));
	result = malloc((ft_strlen(buff) -i + 1) * sizeof(char));
	if (!result)
		return (ft_error(buff, 0));
	i++;
	while (buff[i])
		result[j++] = buff[i++];
	result[j] = 0;
	free(buff);
	return (result);
}

static char	*ft_get_buff(int fd, char *buff)
{
	char	*read_buff;
	int		status;
	char	*tmp;

	read_buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buff)
		return (ft_error(buff, 0));
	status = 1;
	while (status)
	{
		status = read(fd, read_buff, BUFFER_SIZE);
		if (status == -1)
			return (ft_error(read_buff, buff));
		read_buff[status] = 0;
		tmp = ft_strjoin(buff, read_buff);
		free(buff);
		buff = tmp;
		if (!buff)
			return (ft_error(read_buff, 0));
		if (ft_strchr(read_buff, '\n'))
			break ;
	}
	free(read_buff);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char		buff[OPEN_MAX][BUFFER_SIZE];
	char			*tmp;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = ft_get_buff(fd, ft_strdup(buff[fd]));
	if (!tmp)
		return (NULL);
	line = get_line(tmp);
	if (!line)
	{
		free(tmp);
		buff[fd][0] = 0;
		return (NULL);
	}
	tmp = get_next_buff(tmp);
	if (!tmp)
		return (NULL);
	ft_strlcpy(buff[fd], tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (line);
}
// # include <stdio.h>

// int	main(void)
// {
// 	int	fd;
// 	int	i;
// 	char *str;

// 	i = 0;
// 	fd = open("test.txt", O_RDONLY);
// 	while (i < 14)
// 	{
// 		str = get_next_line(fd);
// 		printf("%i: %s", i, str);
// 		free(str);
// 		i++;
// 	}
// 	close(fd);
// }
