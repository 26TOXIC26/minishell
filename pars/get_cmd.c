/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:12:44 by amousaid          #+#    #+#             */
/*   Updated: 2024/09/07 11:24:00 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*add_first_to_tlist(char **tab, int *i)
{
	t_list	*cmd;

	if ((tab[*i] && tab[*i][0]) || (tab[*i + 1] && is_type(tab[*i
				+ 1]) == PIPE))
		cmd = ft_lstnew(tab[*i], is_type(tab[*i]));
	else
	{
		while ((tab[*i] && !tab[*i][0]) && (tab[*i + 1] && is_type(tab[*i
					+ 1]) != PIPE))
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
		if (tab[*i][0] != '\0' || (tab[*i + 1] && is_type(tab[*i + 1]) == PIPE))
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

t_list	*init_cmd(t_main *list)
{
	char	**tab;
	int		i;
	t_list	*cmd;

	i = 0;
	tab = ft_split(list->mini.line);
	if (!tab)
		return (NULL);
	tab = ft_expand(tab, list);
	cmd = add_first_to_tlist(tab, &i);
	add_to_tlist(cmd, tab, &i);
	arry_c(tab);
	if (check_list(cmd, list))
	{
		free_cmd(cmd);
		return (NULL);
	}
	remove_quotes(cmd);
	return (cmd);
}
