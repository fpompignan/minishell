/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:19:45 by fassier-          #+#    #+#             */
/*   Updated: 2022/03/21 18:22:04 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		result[i] = s1[i];
	while (s2[j] != '\0')
		result[i++] = s2[j++];
	result[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free (s1);
	return (result);
}

static char	*ft_read_and_save(int fd, char *save)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;

	ret = 1;
	while (ft_strchr(save, '\n') == 0 && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		save = ft_strjoin2(save, buf);
	}
	return (save);
}

static char	*ft_get_line(char *save)
{
	int		i;
	char	*result;

	if (save[0] == 0)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	result = malloc(sizeof(char) * (i + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		result[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		result[i] = save[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}	

static char	*ft_save(char *save)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	result = malloc(sizeof(char) * (ft_strlen(save) - i));
	if (result == NULL)
		return (NULL);
	i++;
	j = 0;
	while (save[i] != '\0')
		result[j++] = save[i++];
	result[j] = '\0';
	free(save);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read_and_save(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_save(save);
	return (line);
}
