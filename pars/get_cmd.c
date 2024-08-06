/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:12:44 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/06 08:30:02 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*add_first_to_tlist(char **tab, int *i)
{
	t_list	*cmd;

	if (tab[*i][0])
		cmd = ft_lstnew(tab[*i], is_type(tab[*i]));
	else
	{
		while (tab[*i] && tab[*i][0] == '\0')
			(*i)++;
		cmd = ft_lstnew(tab[*i], is_type(tab[*i]));
	}
	if (tab[*i])
		(*i)++;
	return (cmd);
}

void	add_to_tlist(t_list *cmd, char **tab, int *i)
{
	while (tab[*i])
	{
		if (tab[*i][0] != '\0')
		{
			if (ft_lstlast(cmd)->type != PIPE && ft_lstlast(cmd)->type != STR
				&& ft_lstlast(cmd)->type != RFILE && is_type(tab[*i]) == STR)
				ft_lstadd_back(&cmd, ft_lstnew(tab[*i], RFILE));
			else
				ft_lstadd_back(&cmd, ft_lstnew(tab[*i], is_type(tab[*i])));
		}
		(*i)++;
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
	tab = ft_expand(tab, &list->mini, list->colec);
	cmd = add_first_to_tlist(tab, &i);
	add_to_tlist(cmd, tab, &i);
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	if (check_list(cmd))
	{
		free_list(cmd);
		return (NULL);
	}
	remove_quotes(cmd, list->colec);
	return (cmd);
}
