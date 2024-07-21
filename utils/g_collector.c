/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_collector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:15:58 by bamssaye          #+#    #+#             */
/*   Updated: 2024/07/21 14:27:03 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void del_collec(void *value)
{
    free(value);
    value = NULL;
}

void    ft_lstdelone_collec(t_colec *lst, void (*del)(void*))
{
    if (!lst || !del)
        return ;
    del_collec(lst->ptr);
    free(lst);
    lst = NULL;
}

void    ft_lstclear_collec(t_colec **lst, void (*del)(void*))
{
    t_colec    *tmp;

    if (!lst || !del || !(*lst))
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        ft_lstdelone_collec(*lst, del);
        *lst = tmp;
    }
    *lst = NULL;
    exit(1);
}


t_colec    *ft_lstnew_collec(void *content)
{
    t_colec    *head;

    head = malloc(sizeof(t_colec));
    if (!head)
        return (NULL);
    head->ptr = content;
    head->next = NULL;
    return (head);
}
t_colec    *ft_lstlast_collec(t_colec *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next != NULL)
        lst = lst->next;
    return (lst);
}

void    ft_lstadd_back_collec(t_colec **lst, t_colec *new)
{
    t_colec    *ptr_node;

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

void ft_collectore(t_global *data, void *ptr)
{
    t_colec *node;
    
    node = ft_lstnew_collec(ptr);
    ft_lstadd_back_collec(&data->colec , node);
}

