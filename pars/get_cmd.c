/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:12:44 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/04 11:36:40 by amousaid         ###   ########.fr       */
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
        if (line[i] == '|' || (line[i] == '>' && line[i+1] != '>') || (line[i] == '<' && line[i + 1] != '<'))
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

t_list *init_cmd(t_minishell *mini)
{
    char **tab;
    int i;
    t_list *cmd;
    
    i = 0;    
    tab = ft_split(mini->line);
    while (tab[i])
    {
        if (i == 0 && tab[0][0] != '>' && tab[0][0] != '<')
            cmd = ft_lstnew(tab[i], CMD);
        else if (i == 0 && (tab[0][0] == '>' || tab[0][0] == '<'))
        {
            if (tab[0][0] == '>' && tab[0][1] != '>')
                cmd = ft_lstnew(tab[i], GREAT);
            else if (tab[0][0] == '<' && tab[0][1] != '<')
                cmd = ft_lstnew(tab[i], LESS);
            else if (tab[0][0] == '>' && tab[0][1] == '>')
                cmd = ft_lstnew(tab[i], APPEND);
            else if (tab[0][0] == '<' && tab[0][1] == '<')
                cmd = ft_lstnew(tab[i], HEREDOC);
        }
        else
        {
            if (ft_lstlast(cmd)->type == PIPE || ft_lstlast(cmd)->type == GREAT || ft_lstlast(cmd)->type == LESS || ft_lstlast(cmd)->type == APPEND || ft_lstlast(cmd)->type == HEREDOC)
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], CMD)); 
            else if (tab[i][0] == '\'' || tab[i][0] == '\"')
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], OPR));
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
            else if (ft_lstlast(cmd)->type == CMD)
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], OPR));
            else
                ft_lstadd_back(&cmd, ft_lstnew(tab[i], OPR));
        }
        i++;
    }
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    return (cmd);
}