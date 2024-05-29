/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/05/29 03:33:52 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <stdio.h>

// bismilah

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
    
    i = 0;
    while(env[i])
        i++;
    mini->env = _malloc(sizeof(char*) * i + 1);
    mini->env[i] = NULL;
    len = i;
    i = -1;
    size_t l;
    while (++i < len)
    {
        l =  ft_strlen(env[i]);
        mini->env[i] = malloc(sizeof(char) * l + 1);
        ft_strlcpy(mini->env[i], env[i], l + 1);
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

void exec_cmd(char *mini)
{
    pid_t pid;
    char **args = NULL;
    args = malloc(sizeof(char*) * 2);
    
    args[0] = strdup(mini);
    args[1] = NULL;
    pid = fork();
    if (pid == 0)
        execve(args[0],args, NULL);
    else
        waitpid(pid, NULL, 0);
}

void edit_old_pwd(size_t i, t_minishell *mini)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    free(mini->env[i]);
    mini->env[i] = malloc(sizeof(char) * ft_strlen(pwd) + 8);
    ft_strlcpy(mini->env[i], "OLDPWD=", 8);
    ft_strlcpy(mini->env[i] + 7, pwd, ft_strlen(pwd) + 1);
}

void edit_pwd(size_t i, t_minishell *mini)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    free(mini->env[i]);
    mini->env[i] = malloc(sizeof(char) * ft_strlen(pwd) + 5);
    ft_strlcpy(mini->env[i], "PWD=", 5);
    ft_strlcpy(mini->env[i] + 4, pwd, ft_strlen(pwd) + 1);
}

int main(int ac, char **av, char **env)
{
    t_minishell mini;
    
    (void)ac;
    (void)av;
    
    int i = 1;
    ft_init(env, &mini);
    plus_shlvl(find_env("SHLVL", &mini), &mini);
    while (i)
    {        
        
        mini.line = readline(CYAN BOLD "MINIHELL $> "RESET);
        if (!ft_strncmp(mini.line, "env", ft_strlen("env")))
            print_env(&mini);
        else if (!ft_strncmp(mini.line, "pwd", ft_strlen("pwd")))
            ft_pwd();
        else if (!ft_strncmp(mini.line, "exit", ft_strlen("exit")))
            break ;
        else if (!ft_strncmp(mini.line, "cd", ft_strlen("cd")))
        {
            edit_old_pwd(find_env("OLDPWD", &mini) ,&mini);
            if (ft_strlen(mini.line) == 2)
                ft_cd(getenv("HOME"));
            else
                ft_cd(mini.line + 3);
            edit_pwd(find_env("PWD", &mini), &mini);
        }
        // else
        //     exec_cmd(mini.line);

        //cd need to be fixed in old path

        free(mini.line);
        // mini.line = NULL;
    }
    return (0);
}
