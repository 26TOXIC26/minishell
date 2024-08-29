/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:06:29 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/29 00:20:45 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_space(char *s)
{
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '\0')
		return (0);
	return (1);
}

int	chr_cmp(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\0')
		return (1);
	return (0);
}

int	count_her(t_list *cmd)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	psyntax_error(char *msg)
{
	ft_putstr_fd(EMSG, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
	return (2);
}
