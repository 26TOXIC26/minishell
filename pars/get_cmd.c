/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:12:44 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/12 23:24:58 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_space(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
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
			j = j + 2;
		else if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<'
				&& line[i + 1] == '<'))
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
		if (line[i] == '\'')
		{
			new_line[j] = line[i];
			j++;
			i++;
			while (line[i] && line[i] != '\'')
			{
				new_line[j] = line[i];
				j++;
				i++;
			}
			new_line[j] = line[i];
			j++;
		}
		else if (line[i] == '\"')
		{
			new_line[j] = line[i];
			j++;
			i++;
			while (line[i] && line[i] != '\"')
			{
				new_line[j] = line[i];
				j++;
				i++;
			}
			new_line[j] = line[i];
			j++;
		}
		else if (line[i] == '|' || (line[i] == '>' && line[i + 1] != '>')
			|| (line[i] == '<' && line[i + 1] != '<'))
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
		else if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<'
				&& line[i + 1] == '<'))
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

int	is_type(char *str)
{
	if (str)
	{
		if (str[0] == '|')
			return (PIPE);
		else if (str[0] == '>' && str[1] != '>')
			return (OUT);
		else if (str[0] == '<' && str[1] != '<')
			return (IN);
		else if (str[0] == '>' && str[1] == '>')
			return (APPEND);
		else if (str[0] == '<' && str[1] == '<')
			return (HEREDOC);
		else
			return (STR);
	}
	return (0);
}

t_list	*init_cmd(f_list *list)
{
	char	**tab;
	int		i;
	t_list	*cmd;

	i = 0;
	tab = ft_split(list->mini.line);
	i = 0;
	if (!tab)
		return (NULL);
	ft_dsymbol(tab, &list->mini);
	cmd = ft_lstnew(tab[i], is_type(tab[i]));
	i++;
	while (tab[i])
	{
		if (ft_lstlast(cmd)->type != PIPE && ft_lstlast(cmd)->type != STR
			&& ft_lstlast(cmd)->type != RFILE && is_type(tab[i]) == STR)
			ft_lstadd_back(&cmd, ft_lstnew(tab[i], RFILE));
		else
			ft_lstadd_back(&cmd, ft_lstnew(tab[i], is_type(tab[i])));
		i++;
	}
	i = 0;
	while (tab[i])
		free(tab[i++]);
	if (check_list(cmd) == 1)
		return (NULL);
	return (cmd);
}
