/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:00:19 by douattar          #+#    #+#             */
/*   Updated: 2022/02/01 10:25:50 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_list	*ft_lstnew(int content)
{
	t_list	*res;

	res = (t_list *)malloc(sizeof(t_list));
	if (res == NULL)
		return (NULL);
	res->next = NULL;
	res->n = content;
	return (res);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize(t_list *lst)
{
	t_list	*res;
	int		i;

	if (lst == NULL)
		return (0);
	res = lst;
	i = 0;
	while (res != NULL)
	{
		res = res->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*res;

	if (lst == NULL)
		return (NULL);
	res = lst;
	while (res->next != NULL)
		res = res->next;
	return (res);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst == NULL || new == NULL)
		return ;
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}
