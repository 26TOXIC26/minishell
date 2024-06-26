/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/06/26 02:03:50 by abdelilah        ###   ########.fr       */
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
int main(int ac, char **av, char **env)
{
    t_minishell mini;
    t_list *cmd;
    
    (void)ac;
    (void)av;
    cmd = NULL;
    ft_init(env, &mini);
    plus_shlvl(find_env("SHLVL", &mini), &mini);
    while (1)
    {
        mini.line = readline(CYAN BOLD "MINIHELL $> "RESET);
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
    }
    return (0);
}
