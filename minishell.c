/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/07/21 15:37:51 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void ft_empty_env(t_minishell *mini)
{
    mini->env = _malloc(sizeof(char *) * 4);
    mini->env[0] = ft_strjoin("PWD=" , getcwd(NULL, 0));
    mini->env[1] = ft_strdup("SHLVL=1");
    mini->env[2] = ft_strdup("_=/usr/bin/env");
}

f_list *init_main_list(t_command *command)
{
    f_list *main_list;

    main_list = _malloc(sizeof(f_list));
    main_list->cmd = command;
    main_list->exit_status = 0;
    return (main_list);
}

int main(int ac, char **av, char **env)
{
    t_minishell mini;
    t_list *cmd;
    t_command *command;
    
    (void)ac;
    (void)av;
    cmd = NULL;
    command = NULL;
    if (!env[0])
        ft_empty_env(&mini);
    else
    {
        ft_init(env, &mini);
        plus_shlvl(find_env("SHLVL", &mini), &mini);
    }
    while (1)
    {
        signal(SIGINT, sig_handler);
        signal(SIGQUIT, SIG_IGN);
        mini.line = readline(CYAN BOLD "MINIHELL $> "RESET);
        if (!mini.line)
        {
            printf("exit\n");
            break;
        }
        if (mini.line[0] != '\0' && is_space(mini.line))
        {
            add_history(mini.line);
            if (check_syntax(mini) == 1)
            {
                mini.line = add_space(mini.line);
                cmd = init_cmd(&mini);
                if (cmd)
                    command = init_command(cmd);
                free(mini.line);
                mini.line = NULL;
            }
            // free_list(cmd); 
            // free_command(command);
        }
        // while (command)
        // {
        //     if (command->redir)
        //     {
        //         while (command->redir)
        //         {
        //             printf("redir: %s\n", command->redir->file);
        //             printf("type: %d\n", command->redir->type);
        //             command->redir = command->redir->next;
        //         }
        //     }
        //     command = command->next;
        // }
        // while (cmd)
        // {
        //     printf("token: %s\n", cmd->token);
        //     printf("type: %d\n", cmd->type);
        //     cmd = cmd->next;
        // }
        //////////////////////////
        //_execinit(command, cmd, &mini);
        printf("line: %s\n", mini.line);
    }
    (void)command;
    free(mini.line);
    free(mini.env);
    return (0);
}
