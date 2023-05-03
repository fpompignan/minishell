/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:12:21 by douattar          #+#    #+#             */
/*   Updated: 2022/04/14 19:17:31 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lstdelone(t_list *lst)
{
	if (lst != NULL)
		free(lst);
}

void	ft_lstdelone_last(t_list *lst)
{
	while (lst->next->next != NULL)
		lst = lst->next;
	if (lst->next != NULL)
		free(lst->next);
	lst->next = NULL;
}

void	ft_lstclear(t_list *lst)
{
	if (lst == NULL)
		return ;
	else
		ft_lstclear(lst->next);
	free(lst);
}
