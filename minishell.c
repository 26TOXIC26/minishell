/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/07/07 23:50:10 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int take_cmd(t_minishell *mini, t_list *cmd)
{
    if (!ft_strncmp(cmd->token, "env\0", ft_strlen("env") + 1))
                print_env(mini->env, 0);
    else if (!ft_strncmp(cmd->token, "pwd\0", ft_strlen("pwd") + 1))
        ft_pwd();
    else if (!ft_strncmp(cmd->token, "exit\0", ft_strlen("exit") + 1))
        return (0);
    else if (!ft_strncmp(cmd->token, "cd\0", ft_strlen("cd") + 1))
    {
        edit_old_pwd(find_env("OLDPWD", mini) ,mini);
        if (ft_strlen(mini->line) == 2)
            ft_cd(getenv("HOME"));
        else
            ft_cd(mini->line + 3);
        edit_pwd(find_env("PWD", mini), mini);
    }
    else if (!ft_strncmp(cmd->token, "echo\0", ft_strlen("echo") + 1))
        ft_echo(cmd->next);
    else if (!ft_strncmp(cmd->token, "unset\0", ft_strlen("unset") + 1))
        ft_unset(cmd->next, mini);
    else if (!ft_strncmp(cmd->token, "export\0", ft_strlen("export") + 1))
        ft_export(cmd->next, mini);
    // else
    //     exec_cmd(mini->line);
    return (1);
}

void ft_empty_env(t_minishell *mini)
{
    mini->env = _malloc(sizeof(char *) * 4);
    mini->env[0] = ft_strjoin("PWD=" , getcwd(NULL, 0));
    mini->env[1] = ft_strdup("SHLVL=1");
    mini->env[2] = ft_strdup("_=/usr/bin/env");
}

int main(int ac, char **av, char **env)
{
    t_minishell mini;
    t_list *cmd;
    t_list *tmp;
    
    (void)ac;
    (void)av;
    cmd = NULL;
    if (!env[0])
        ft_empty_env(&mini);
    else
        ft_init(env, &mini);
    plus_shlvl(find_env("SHLVL", &mini), &mini);
    while (1)
    {
        mini.line = readline(CYAN BOLD "MINIHELL $> "RESET);
        if (mini.line[0] != '\0')
        {
            if (is_space(mini.line))
                add_history(mini.line);
            mini.line = add_space(mini.line);
            if (check_syntax(mini) == 1)
            {
                cmd = init_cmd(&mini);
                if (mini.line[0] != '\0')
                    if (take_cmd(&mini, cmd) == 0)
                        break;
                free(mini.line);
                mini.line = NULL;
            }
            tmp = cmd;
            // while (tmp)
            // {
            //     printf("token ---->    %s\n", tmp->token);
            //     printf("type  ---->    %d\n", tmp->type);
            //     tmp = tmp->next;
            // }
            while (cmd)
            {
                tmp = cmd->next;
                free(cmd->token);
                free(cmd);
                cmd = tmp;
            }    
        }
    }
    free(mini.line);
    free(mini.env);
    return (0);
}
