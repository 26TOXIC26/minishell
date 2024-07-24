/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 06:36:59 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/12 23:34:28 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->token);
		free(tmp);
	}
}

void	free_command(t_command *cmd)
{
	t_redir	*tmp;
	int		i;

	i = 0;
	while (cmd->redir)
	{
		tmp = cmd->redir;
		cmd->redir = cmd->redir->next;
		free(tmp->file);
		free(tmp);
	}
	while (cmd->options[i])
	{
		free(cmd->options[i]);
		i++;
	}
	free(cmd->options);
	free(cmd);
}
