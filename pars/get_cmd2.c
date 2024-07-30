/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 22:05:42 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/30 23:51:41 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_quotes(char *line, char *new_line, char quote, int *i, int *j)
{
	new_line[(*j)++] = line[(*i)++];
	while (line[(*i)] && line[(*i)] != quote)
		new_line[(*j)++] = line[(*i)++];
	if (line[(*i)] == quote)
		new_line[(*j)++] = line[(*i)];
}

void	size_nline(char *line, int i, int *j)
{
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		else if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
		}
		else if (line[i] == '|' || (line[i] == '>' && line[i + 1] != '>')
			|| (line[i] == '<' && line[i + 1] != '<'))
			(*j) = (*j) + 2;
		else if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<'
				&& line[i + 1] == '<'))
		{
			(*j) = (*j) + 2;
			i++;
		}
		i++;
	}
}

void	add_space2(char *line, char *new_line, int *i, int *j)
{
	if (line[(*i)] == '|' || (line[(*i)] == '>' && line[(*i) + 1] != '>')
		|| (line[(*i)] == '<' && line[(*i) + 1] != '<'))
	{
		new_line[(*j)++] = ' ';
		new_line[(*j)++] = line[(*i)];
		new_line[(*j)++] = ' ';
	}
	else if (line[(*i)] == ' ')
		new_line[(*j)++] = ' ';
	else if ((line[(*i)] == '>' && line[(*i) + 1] == '>') || (line[(*i)] == '<'
			&& line[(*i) + 1] == '<'))
	{
		new_line[(*j)++] = ' ';
		new_line[(*j)++] = line[(*i)];
		new_line[(*j)++] = line[(*i) + 1];
		new_line[(*j)++] = ' ';
		(*i)++;
	}
	else
		new_line[(*j)++] = line[(*i)];
}

char	*add_space(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	size_nline(line, 0, &j);
	new_line = _malloc(sizeof(char) * (ft_strlen(line) + j + 1));
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quotes(line, new_line, line[i], &i, &j);
		else
			add_space2(line, new_line, &i, &j);
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
