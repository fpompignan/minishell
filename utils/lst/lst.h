/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douattar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:22:31 by douattar          #+#    #+#             */
/*   Updated: 2022/02/13 14:06:03 by douattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H
# include "s_list.h"
# include "../push_swap.h"

t_list	*ft_lstnew(int content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	top_inverse(t_list **a, t_list **b, int n);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst);
t_list	*create_tab(int *tab, int size);
void	push(t_list **pile_a, t_list **pile_b);
void	swap(int *A, int *B);
void	rotate(t_list **tab);
void	reverse_rotate(t_list **tab);
void	ft_lstclear(t_list *lst);
void	top_two(t_list **a, t_list **b, int n);
int		top(t_list **tab, int n, char *str);
int		find(t_list *tab, int n);
int		closet(t_list *tab, int n);
int		is_swap(t_list **tab, int n, char *str);
void	ft_lstdelone_last(t_list *lst);
int		range(t_list *tab);
int		top_count(t_list **tab, int n);
#endif
