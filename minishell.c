/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/06/13 23:16:30 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"



void    *_malloc(size_t size)
{
    void *ptr;
    
    ptr = malloc(size);
    if (!ptr)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return (ptr);
}

void ft_init(char **env, t_minishell *mini)
{
    int i;
    int len;
    size_t l;
    
    i = 0;
    while(env[i])
        i++;
    mini->env = _malloc(sizeof(char*) * i + 1);
    mini->env[i] = NULL;
    len = i;
    i = -1;
    while (++i < len)
    {
        l =  ft_strlen(env[i]);
        mini->env[i] = malloc(sizeof(char) * l + 1);
        ft_strlcpy(mini->env[i], env[i], l + 1);
    }
    
}


// void exec_cmd(char *mini)
// {
//     pid_t pid;
//     char **args = NULL;
//     args = malloc(sizeof(char*) * 2);
    
//     args[0] = strdup(mini);
//     args[1] = NULL;
//     pid = fork();
//     if (pid == 0)
//         execve(args[0],args, NULL);
//     else
//         waitpid(pid, NULL, 0);
// }

int d2_len(char **str)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    return (i);
}


void edit_old_pwd(size_t i, t_minishell *mini)
{
    char *pwd;
    int j;

    if ((int)i == -1)
    {
        j = d2_len(mini->env);
        pwd = getcwd(NULL, 0);
        mini->env[j] = malloc(sizeof(char) * (ft_strlen(pwd) + 8));
        ft_strlcpy(mini->env[j], "OLDPWD=", 8);
        ft_strlcpy(mini->env[j] + 7, pwd, ft_strlen(pwd) + 1);
        mini->env[j + 1] = NULL;
    }
    else
    {
    pwd = getcwd(NULL, 0);
    free(mini->env[i]);
    mini->env[i] = malloc(sizeof(char) * ft_strlen(pwd) + 8);
    ft_strlcpy(mini->env[i], "OLDPWD=", 8);
    ft_strlcpy(mini->env[i] + 7, pwd, ft_strlen(pwd) + 1);
    }
}

void edit_pwd(size_t i, t_minishell *mini)
{
    char *pwd;
    int j;

    if ((int)i == -1)
    {
        j = d2_len(mini->env);
        pwd = getcwd(NULL, 0);
        mini->env[j] = malloc(sizeof(char) * (ft_strlen(pwd) + 5));
        ft_strlcpy(mini->env[j], "PWD=", 5);
        ft_strlcpy(mini->env[j] + 4, pwd, ft_strlen(pwd) + 1);
        mini->env[j + 1] = NULL;
    }
    else
    {
        
    pwd = getcwd(NULL, 0);
    free(mini->env[i]);
    mini->env[i] = malloc(sizeof(char) * ft_strlen(pwd) + 5);
    ft_strlcpy(mini->env[i], "PWD=", 5);
    ft_strlcpy(mini->env[i] + 4, pwd, ft_strlen(pwd) + 1);
    }
}

int take_cmd(t_minishell *mini, t_list *cmd, char **env)
{
    if (!ft_strncmp(cmd->token, "env\0", ft_strlen("env") + 1))
                print_env(env);
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
        ft_export(cmd->next, mini, env);
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
                if (take_cmd(&mini, cmd, env) == 0)
                    break;
            free(mini.line);
            mini.line = NULL;
        }
    }
    return (0);
}
