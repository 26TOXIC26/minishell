/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:55:25 by abdelilah         #+#    #+#             */
/*   Updated: 2024/07/21 15:20:28 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int find_env(char *str, t_minishell *mini)
{
    int i;
    size_t len;
    
    i = 0;
    
    while (str[i] && str[i] != '=' && str[i] != '+')
        i++;
    len = i;
    i = 0;
    while (mini->env[i])
    {
        if (!ft_strncmp(mini->env[i], str, len) && (mini->env[i][len] == '=' || mini->env[i][len] == '\0'))
            return (i);
        i++;
    }
    return (-1);
}

void plus_shlvl(size_t i, t_minishell *mini)
{
    char *str;
    char *tmp;
    int j;
    
    str = ft_strchr(mini->env[i], '=') + 1;
    j = ft_atoi(str);
    j++;
    tmp = ft_itoa(j);
    ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
    free(tmp);
}