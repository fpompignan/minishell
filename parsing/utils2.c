/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:16:44 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/18 15:11:16 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*f_strdup(char *s)
{
	char	*result;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	size = f_strlen(s);
	result = malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}

char	*f_strjoin2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = malloc(sizeof(char) * (f_strlen(s1) + f_strlen(s2) + 1));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		result[i] = s1[i];
	while (s2[j] != '\0')
		result[i++] = s2[j++];
	result[f_strlen(s1) + f_strlen(s2)] = '\0';
	free (s1);
	return (result);
}

char	*f_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = malloc(sizeof(char) * (f_strlen(s1) + f_strlen(s2) + 1));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		result[i] = s1[i];
	while (s2[j] != '\0')
		result[i++] = s2[j++];
	result[f_strlen(s1) + f_strlen(s2)] = '\0';
	return (result);
}

int	forward_to_first_nonspace_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}
