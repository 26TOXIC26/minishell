/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:59:32 by bamssaye          #+#    #+#             */
/*   Updated: 2024/07/24 05:33:13 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_unset(t_list *cmd, t_minishell *mini)
{
    t_list *tmp;
    int i;

    tmp = cmd;
    while (tmp && !tmp->type)
    {
        i = find_env(tmp->token, mini);
        if (i != -1)
        {
            free(mini->env[i]);
            while (mini->env[i])
            {
                mini->env[i] = mini->env[i + 1];
                i++;
            }
            mini->env[i] = NULL;
        }
        tmp = tmp->next;
    }
}