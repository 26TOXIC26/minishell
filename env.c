/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:55:25 by abdelilah         #+#    #+#             */
/*   Updated: 2024/05/28 12:56:44 by abdelilah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

size_t find_env(char *str, t_minishell *mini)
{
    size_t i;
    size_t len;
    
    i = 0;
    len = ft_strlen(str);
    while (mini->env[i])
    {
        if (!ft_strncmp(mini->env[i], str, len))
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