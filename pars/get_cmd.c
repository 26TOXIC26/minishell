/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:12:44 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/31 19:06:20 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	remove_quotes3(char *str, int *i, int *j, char *new_str)
{
	char	qoute;

	qoute = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != qoute)
	{
		new_str[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	if (str[*i] == qoute)
		(*i)++;
}

char	*remove_quotes2(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = _malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			remove_quotes3(str, &i, &j, new_str);
		else
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

void	remove_quotes(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type != RFILE)
			tmp->token = remove_quotes2(tmp->token);
		tmp = tmp->next;
	}
}

t_list	*init_cmd(f_list *list)
{
	char	**tab;
	int		i;
	t_list	*cmd;

	i = 0;
	tab = ft_split(list->mini.line);
	if (!tab)
		return (NULL);
	tab = ft_expand(tab, &list->mini);
	if (tab[i][0])
		cmd = ft_lstnew(tab[i], is_type(tab[i]));
	else
	{
		while (tab[i] && tab[i][0] == '\0')
			i++;
		cmd = ft_lstnew(tab[i], is_type(tab[i]));
	}
	i++;
	while (tab[i])
	{
		if (tab[i][0] != '\0')
		{	
			if (ft_lstlast(cmd)->type != PIPE && ft_lstlast(cmd)->type != STR
				&& ft_lstlast(cmd)->type != RFILE && is_type(tab[i]) == STR)
				ft_lstadd_back(&cmd, ft_lstnew(tab[i], RFILE));
			else
				ft_lstadd_back(&cmd, ft_lstnew(tab[i], is_type(tab[i])));
		}
		i++;
	}
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	if (check_list(cmd))
	{
		free_list(cmd);
		return (NULL);
	}
	remove_quotes(cmd);
	return (cmd);
}
