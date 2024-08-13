/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:05:14 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/13 11:03:01 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote(t_minishell mini)
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
				printf("quote not closed\n");
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

int	check_syntax2(t_minishell mini)
{
	int	i;

	i = 0;
	while (mini.line[i])
	{
		if (mini.line[i] == '\'' || mini.line[i] == '\"')
			skip_quote(mini.line, &i);
		if (mini.line[i] == '|' && is_space(mini.line + i + 1) == 0)
			return (printf(EMSG " `||' | '\\n'\n") && 0);
		else if ((mini.line[i] == '<' && mini.line[i + 1] == '>')
			|| (mini.line[i] == '>' && mini.line[i + 1] == '<'))
			return (printf(EMSG " `<>'\n") && 0);
		else if (((mini.line[i] == '<' && mini.line[i + 1] == '<')
				|| (mini.line[i] == '>' && mini.line[i + 1] == '>'))
			&& (chr_cmp(mini.line[i + 2]) || is_space(mini.line + i + 2) == 0))
			return (printf(EMSG " `<<' | `>>'\n") && 0);
		else if ((mini.line[i] == '<' || mini.line[i] == '>')
			&& is_space(mini.line + i + 1) == 0)
			return (printf(EMSG " `%c'\n", mini.line[i]) && 0);
		i++;
	}
	return (1);
}

int	check_syntax(t_minishell mini)
{
	if (!check_quote(mini))
		return (0);
	else if (mini.line[0] == '|')
		return (printf(EMSG " `%c'\n", mini.line[0]) && 0);
	else if ((mini.line[0] == '>' || mini.line[0] == '<')
		&& (mini.line[1] == '\0' || is_space(mini.line + 1) == 0
			|| mini.line[1] == '|'))
		return (printf(EMSG " `%c'\n", mini.line[0]) && 0);
	if (check_syntax2(mini) == 0)
		return (0);
	return (1);
}

int	check_list(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	if (tmp->type == PIPE)
		return (printf(EMSG " `%s'\n", tmp->token) && 1);
	while (tmp)
	{
		if ((tmp->type == HEREDOC || tmp->type == APPEND || tmp->type == OUT
				|| tmp->type == IN) && tmp->next && tmp->next->type != RFILE)
			return (printf(EMSG " `%s'\n", tmp->token), 1);
		else if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
			return (printf(EMSG " `%s'\n", tmp->token), 1);
		tmp = tmp->next;
	}
	return (0);
}
