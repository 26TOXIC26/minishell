/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_col1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:15:58 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/19 23:06:52 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



t_colec	*ft_lstnew_collec(void *content)
{
	t_colec	*head;

	head = malloc(sizeof(t_colec));
	if (!head)
		return (NULL);
	head->ptr = content;
	head->next = NULL;
	return (head);
}

t_colec	*ft_lstlast_collec(t_colec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_collec(t_colec **lst, t_colec *new)
{
	t_colec	*ptr_node;

	if (!new || !lst)
		return ;
	if (*lst)
	{
		ptr_node = ft_lstlast_collec(*lst);
		ptr_node->next = new;
	}
	else
		*lst = new;
}

int	ft_collectore(t_colec **data, void *ptr)
{
	t_colec	*node;

	node = ft_lstnew_collec(ptr);
	if (!node)
		return (1);
	ft_lstadd_back_collec(data, node);
	return (0);
}
