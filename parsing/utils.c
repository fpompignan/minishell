/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:03:17 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/26 16:41:03 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

char	*ft_strndup(char *s, int n)
{
	char	*ret;

	ret = NULL;
	if (s)
	{
		ret = malloc(sizeof(char) * (n + 1));
		if (!ret)
			return (NULL);
		ft_strncpy(ret, s, n);
		ret[n] = '\0';
	}
	return (ret);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

char	*ft_strndup_sp(char *s, int n, t_process *process)
{
	char	*ret;

	ret = NULL;
	if (s)
	{
		ret = malloc(sizeof(char) * (n + 1));
		if (!ret)
		{
			printf("minishell: error: malloc faile\n");
			exit_minishell(process);
		}
		ft_strncpy(ret, s, n);
		ret[n] = '\0';
	}
	return (ret);
}
/*
<<<<<<< HEAD:minishell/src/utils.c

char	*ft_strdup(char *s)
{
	char	*result;
	size_t	size;
	size_t	i;

	size = ft_strlen(s);
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

=======
>>>>>>> dev:parsing/utils.c
*/
