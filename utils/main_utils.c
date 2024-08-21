/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:37:30 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/21 00:02:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lstsizess(t_env *lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!lst)
		return (0);
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_main	*_initminish(char **env)
{
	t_main	*minish;

	minish = _malloc(sizeof(t_main));
	minish->cmd = NULL;
	minish->command = NULL;
	minish->exit_status = 0;
	minish->bultin = i_bultin();
	minish->env = set_envc(env);
	return (minish);
}