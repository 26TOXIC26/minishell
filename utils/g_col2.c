/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_col2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:07:27 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/29 03:01:52 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_redi(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->file != NULL)
		{
			free(tmp->file);
			tmp->file = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	free_comd(t_command *cmd)
{
	t_command	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->redir != NULL)
			free_redi(tmp->redir);
		if (tmp->options)
			arry_c(tmp->options);
		free(tmp);
		tmp = NULL;
	}
}

void	free_cmd(t_list *cmd)
{
	t_list	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->token != NULL)
			free(tmp->token);
		free(tmp);
		tmp = NULL;
	}
}

void	free_env(t_env *cmd)
{
	t_env	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->line[0])
			free(tmp->line[0]);
		if (tmp->line[1])
			free(tmp->line[1]);
		free(tmp);
		tmp = NULL;
	}
}
