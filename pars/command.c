/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:49 by abdelilah         #+#    #+#             */
/*   Updated: 2024/07/08 16:04:16 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
        perror("cd");
}

void print_env(char **env, int export)
{
    int i = 0;
    while (env[i])
    {
        if (export == 1)
            printf("declare -x ");
        printf("%s\n", env[i]);
        i++;
    }
}

void ft_echo(t_list *cmd)
{
    t_list *tmp;
    int new_line;

    tmp = cmd;
    new_line = 0;
    if (tmp && tmp->type == 1 && !ft_strncmp(tmp->token, "-n\0", ft_strlen("-n") + 1))
    {
        new_line = 1;
        tmp = tmp->next;
    }
    while (tmp && tmp->type == 1)
    {
        printf("%s ", tmp->token);
        tmp = tmp->next;
    }
    if (!new_line)
        printf("\n");
}

void ft_unset(t_list *cmd, t_minishell *mini)
{
    t_list *tmp;
    int i;

    tmp = cmd;
    if (!tmp || tmp->type != 1)
        printf("unset: not enough arguments\n");
    while (tmp && tmp->type == 1)
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

void sort_env(t_minishell *mini)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (mini->env[i])
    {
        j = i + 1;
        while (mini->env[j])
        {
            if (ft_strncmp(mini->env[i], mini->env[j], ft_strlen(mini->env[i])) > 0)
            {
                tmp = mini->env[i];
                mini->env[i] = mini->env[j];
                mini->env[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void ft_export(t_list *cmd, t_minishell *mini)
{
    t_minishell *tmp;
    int i;

    if (cmd && cmd->token[0]== '=')
    {
        printf("export: not a valid identifier\n");
        return ;
    }
    if (!cmd || cmd->type != 1)
    {
        tmp = malloc(sizeof(t_minishell));
        ft_init(mini->env, tmp);
        sort_env(tmp);
        print_env(tmp->env, 1);
    }
    else if (ft_strchr(cmd->token, '='))
    {
        while (cmd && cmd->type == 1)
        {
            if (find_env(cmd->token, mini) == -1)
            {
                mini->env = ft_realloc(mini->env, (d2_len(mini->env) * sizeof(char *)) + sizeof(char *) + 1);
                mini->env[d2_len(mini->env) + 1] = NULL;
                mini->env[d2_len(mini->env)] = ft_strdup(cmd->token);
            }
            else
            {
                i = find_env(cmd->token, mini);
                free(mini->env[i]);
                mini->env[i] = ft_strdup(cmd->token);
            }
            cmd = cmd->next;
        }
    }
}
