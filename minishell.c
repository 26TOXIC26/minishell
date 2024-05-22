/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/05/21 03:50:50 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// bismi lahe

void ft_init(char **env, t_minishell *mini)
{
    int i;
    int len;
    
    while(env[i])
        i++;
    mini->env = malloc(sizeof(char*) * i + 1);
    mini->env[i] = NULL;
    len = i;
    i = -1;
    char l;
    while (++i < len)
    {
        l =  ft_strlen(env[i]);
        mini->env[i] = malloc(sizeof(char) * l + 1);
        mini->env[i][l] = '\0';   
    }
}
int main(int ac, char **av, char **env)
{
    t_minishell mini;
    
    (void)ac;
    (void)av;
    
    int i = 1;
    ft_init(env, &mini);
    while (i)
    {
        // printf("L3ZAWi -> ");
        
        mini.line = readline("L3ZAWi -> ");
        if (!ft_strncmp(mini.line, "env", ft_strlen("env")))
            printf("hello %s", mini.env[1]);
        if (!ft_strncmp(mini.line, "exit", ft_strlen("exit")))
            i = 1;
        // mini.line = NULL;
    }
    return (0);
}


