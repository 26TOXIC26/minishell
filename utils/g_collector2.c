/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_collector2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:07:27 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/13 10:07:59 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	del_collec(void *value)
{
	free(value);
	value = NULL;
}

void	ft_lstdelone_collec(t_colec *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del_collec(lst->ptr);
	free(lst);
	lst = NULL;
}
