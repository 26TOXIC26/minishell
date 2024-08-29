/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:05:14 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/29 00:17:48 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote(t_minishell mini, t_main *m)
{
	int		i;
	char	q;

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
				ft_putstr_fd("quotes not closed\n", 2);
				m->exit_status = 2;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	skip_quote(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] != quote && line[*i])
		(*i)++;
}

int	check_syntax2(t_minishell mini, t_main *m)
{
	int	i;

	i = 0;
	while (mini.line[i])
	{
		if (mini.line[i] == '\'' || mini.line[i] == '\"')
			skip_quote(mini.line, &i);
		if (mini.line[i] == '|' && is_space(mini.line + i + 1) == 0)
			return ((m->exit_status = psyntax_error("`||' | '\\n'")), 0);
		else if ((mini.line[i] == '<' && mini.line[i + 1] == '>')
			|| (mini.line[i] == '>' && mini.line[i + 1] == '<'))
			return ((m->exit_status = psyntax_error(" `<>'")), 0);
		else if (((mini.line[i] == '<' && mini.line[i + 1] == '<')
				|| (mini.line[i] == '>' && mini.line[i + 1] == '>'))
			&& (chr_cmp(mini.line[i + 2]) || is_space(mini.line + i + 2) == 0))
			return ((m->exit_status = psyntax_error(" `<<' | `>>'")), 0);
		else if ((mini.line[i] == '<' || mini.line[i] == '>')
			&& is_space(mini.line + i + 1) == 0)
			return ((m->exit_status = psyntax_error(&mini.line[i])), 0);
		i++;
	}
	return (1);
}

int	check_syntax(t_minishell mini, t_main *m)
{
	if (!check_quote(mini, m))
		return (0);
	else if (mini.line[0] == '|')
		return ((m->exit_status = psyntax_error(&mini.line[0])), 0);
	else if ((mini.line[0] == '>' || mini.line[0] == '<')
		&& (mini.line[1] == '\0' || is_space(mini.line + 1) == 0
			|| mini.line[1] == '|'))
		return ((m->exit_status = psyntax_error(&mini.line[0])), 0);
	if (check_syntax2(mini, m) == 0)
		return (0);
	return (1);
}

int	check_list(t_list *cmd, t_main *m)
{
	t_list	*tmp;

	tmp = cmd;
	if (tmp->type == PIPE)
		return ((m->exit_status = psyntax_error(tmp->token)), 1);
	while (tmp)
	{
		if ((tmp->type == HEREDOC || tmp->type == APPEND || tmp->type == OUT
				|| tmp->type == IN) && tmp->next && tmp->next->type != RFILE)
			return ((m->exit_status = psyntax_error(tmp->token)), 1);
		else if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
			return ((m->exit_status = psyntax_error(tmp->token)), 1);
		tmp = tmp->next;
	}
	return (0);
}
