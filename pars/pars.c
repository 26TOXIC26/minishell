/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:05:14 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/12 22:24:27 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
        else if ((mini.line[i] == '<' && mini.line[i + 1] == '>') || (mini.line[i] == '>' && mini.line[i + 1] == '<'))
            return (printf("syntax error near unexpected token `<>'\n") && 0);
        else if (((mini.line[i] == '<' && mini.line[i + 1] == '<') || (mini.line[i] == '>' && mini.line[i + 1] == '>')) && (chr_cmp(mini.line[i + 2]) || is_space(mini.line + i + 2) == 0))
            return (printf("syntax error near unexpected token `<<|' or `>>|'\n") && 0);
        else if ((mini.line[i] == '<' || mini.line[i] == '>') && is_space(mini.line + i + 1) == 0)
            return (printf("syntax error near unexpected token `%c'\n", mini.line[i]) && 0);
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
    else if ((mini.line[0] == '>' || mini.line[0] == '<') && (mini.line[1] == '\0' || is_space(mini.line + 1) == 0 || mini.line[1] == '|' || mini.line[1] == '&' || mini.line[1] == ';' || mini.line[1] == '-'))
        return (printf("syntax error near unexpected token `%c'\n", mini.line[0]) && 0);
    if (check_syntax2(mini) == 0)
        return (0);
    return (1);
}

int check_list(t_list *cmd)
{
    t_list *tmp;

    tmp = cmd;
    while (tmp)
    {
        if ((tmp->type == HEREDOC || tmp->type == APPEND || tmp->type == OUT || tmp->type == IN) && tmp->next->type != FILE)
            return (printf("syntax error near unexpected token `%s'\n", tmp->token) && 1);
        tmp = tmp->next;
    }
    return (0);
}
