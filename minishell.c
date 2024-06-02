/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:08 by bamssaye          #+#    #+#             */
/*   Updated: 2024/06/02 11:01:47 by codespace        ###   ########.fr       */
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

int check_quote(t_minishell mini)
{
    int i;
    char q;

    i = 0;
    while (mini.line[i])
    {
        if (mini.line[i] == '\'' || mini.line[i] == '\"')
        {
            q = mini.line[i];
            i++;
            while (mini.line[i] != q && mini.line[i])
                i++;
            if (mini.line[i] != q)
            {
                printf("quote not closed\n");
                return (0);
            }
        }
        i++;
    }
    return (1);
}

int    is_space(char *s)
{
    while ((*s >= 9 && *s <= 13) || *s == 32)
        s++;
    if (*s == '\0')
         return (0);
    return (1);    
}

int check_syntax2(t_minishell mini)
{
    int i;

    i = 0;
    while (mini.line[i])
    {
        if (mini.line[i] == '|' && (is_space(mini.line + i + 1) == 0 || mini.line[i + 1] == '|'))
            return (printf("syntax error near unexpected token `||' or 'newline'\n") && 0);
        else if (mini.line[i] == '&' || mini.line[i] == ';')
            return (printf("syntax error near unexpected token `%c'\n", mini.line[i]) && 0);
        else if (mini.line[i] == '<' && mini.line[i + 1] == '>')
            return (printf("syntax error near unexpected token `<>'\n") && 0);
        else if (mini.line[i] == '>' && mini.line[i + 1] == '<')
            return (printf("syntax error near unexpected token `><'\n") && 0);
        else if (mini.line[i] == '<' && mini.line[i + 1] == '<' && mini.line[i + 2] == '<')
            return (printf("syntax error near unexpected token `<<<'\n") && 0);
        else if (mini.line[i] == '>' && mini.line[i + 1] == '>' && mini.line[i + 2] == '>')
            return (printf("syntax error near unexpected token `>>>'\n") && 0);
        else if (mini.line[i] == '<' && mini.line[i + 1] == '<' && mini.line[i + 2] == '>')
            return (printf("syntax error near unexpected token `<<<>'\n") && 0);
        else if (mini.line[i] == '>' && mini.line[i + 1] == '>' && mini.line[i + 2] == '<')
            return (printf("syntax error near unexpected token `>><'\n") && 0);
        else if (mini.line[i] == '>' && mini.line[i + 1] == '>' && mini.line[i + 2] == '>')
            return (printf("syntax error near unexpected token `>>>'\n") && 0);
        else if (mini.line[i] == '<' && mini.line[i + 1] == '<' && mini.line[i + 2] == '<')
            return (printf("syntax error near unexpected token `<<<'\n") && 0);
        else if (mini.line[i] == '>' && mini.line[i + 1] == '>' && mini.line[i + 2] == '>')
            return (printf("syntax error near unexpected token `>>>'\n") && 0);
        else if (mini.line[i] == '<' && mini.line[i + 1] == '<' && mini.line[i + 2] == '>')
            return (printf("syntax error near unexpected token `<<<>'\n") && 0);
        else if (mini.line[i] == '>' && mini.line[i + 1] == '>' && mini.line[i + 2] == '<')
            return (printf("syntax error near unexpected token `>><'\n") && 0);
        i++;
    }
    return (1);
}

int check_syntax(t_minishell mini)
{
    if (!check_quote(mini))
        return (0);
    else if (mini.line[0] == '|')
        return (printf("syntax error near unexpected token `%c'\n", mini.line[0]) && 0);
    else if ((mini.line[0] == '>' || mini.line[0] == '<') && (mini.line[1] == '\0' || mini.line[1] == '|' || mini.line[1] == ';'))
        return (printf("syntax error near unexpected token `%c'\n", mini.line[0]) && 0);
    else if (((mini.line[0] == '>' && mini.line[1] == '>')  || (mini.line[0] == '<' &&  mini.line[1] == '<')) && mini.line[2] == '\0')
        return (printf("syntax error near unexpected token `>>' OR '<<'\n") && 0);
    else if ((mini.line[0] == '<' && mini.line[1] == '>') || (mini.line[0] == '>' && mini.line[1] == '<'))
        return (printf("syntax error near unexpected token `><' OR '<>'\n") && 0);
    if (check_syntax2(mini) == 0)
        return (0);
    return (1);
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
        add_history(mini.line);
        if (check_syntax(mini) == 1)
        {
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
            free(mini.line);
            // mini.line = NULL
        }
    }
    return (0);
}
