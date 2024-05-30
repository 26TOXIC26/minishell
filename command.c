/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:49 by abdelilah         #+#    #+#             */
/*   Updated: 2024/05/30 06:19:45 by abdelilah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void ft_pwd(void)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
    free(pwd);
}

void ft_cd(char *path)
{
    if (chdir(path) == -1)
    {
        perror("cd");
    }
}

void print_env(t_minishell *mini)
{
    int i = 0;
    while (mini->env[i])
    {
        printf("%s\n", mini->env[i]);
        i++;
    }
}