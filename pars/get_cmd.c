/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:12:44 by amousaid          #+#    #+#             */
/*   Updated: 2024/06/06 20:22:44 by abdelilah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *add_space(char *line)
{
    int i;
    int j;
    char *new_line;

    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '|' || (line[i] == '>' && line[i+1] != '>') || (line[i] == '<' && line[i + 1] != '<'))
            j = j + 2;
        else if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
        {
            j = j + 2;
            i++;
        }
        i++;
    }
    new_line = _malloc(sizeof(char) * (ft_strlen(line) + j + 1));
    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '|' || line[i] == '>' || line[i] == '<')
        {
            new_line[j] = ' ';
            new_line[j + 1] = line[i];
            new_line[j + 2] = ' ';
            j = j + 3;
        }
        else if (line[i] == ' ')
        {
            new_line[j] = ' ';
            j++;
        }
        else if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
        {
            new_line[j] = ' ';
            new_line[j + 1] = line[i];
            new_line[j + 2] = line[i + 1];
            new_line[j + 3] = ' ';
            j = j + 4;
            i++;
        }
        else
        {
            new_line[j] = line[i];
            j++;
        }
        i++;
    }
    new_line[j] = '\0';
    return (new_line);
}

void init_cmd(t_minishell *mini, t_list *cmd)
{
    char **tab;
    int i;
    
    i = 0;    
    tab = ft_split(mini->line);
    while (tab[i])
    {
        if (i == 0)
            cmd = ft_lstnew(tab[i], CMD);
        else
        {
            if (tab[i][0] == '-')
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], OPR));
            else if (tab[i][0] == '\'' || tab[i][0] == '\"')
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], QUOTE));
            else if (tab[i][0] == '|')
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], PIPE));
            else if (tab[i][0] == '>' && tab[i][1] != '>')
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], GREAT));
            else if (tab[i][0] == '<' && tab[i][1] != '<')
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], LESS));
            else if (tab[i][0] == '>' && tab[i][1] == '>')
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], APPEND));
            else if (tab[i][0] == '<' && tab[i][1] == '<')
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], HEREDOC));
            else if (tab[i][0] == '$')
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], DOLLAR));
        }
        i++;
    }
    while (cmd)
    {
        printf("%s\n", cmd->token);
        printf("%d\n\n", cmd->type);
        cmd = cmd->next;
    }
}