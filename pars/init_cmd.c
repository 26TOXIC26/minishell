/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:27:55 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/06 09:07:20 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redir	*new_redir(t_list *list, t_colec *colec)
{
	t_redir	*redir;

	redir = _malloc(sizeof(t_redir));
	ft_collectore(&colec, redir);
	redir->type = list->type;
	redir->file = list->next->token;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir *redir, t_list *list, t_colec *colec)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir(list, colec);
}

t_command	*init_command(t_list *list, t_colec *colec)
{
	t_command	*cmd;
	t_list		*tmp;
	int			options;
	int			redr;

	tmp = list;
	redr = 0;
	cmd = _malloc(sizeof(t_command));
	ft_collectore(&colec, cmd);
	cmd->redir = NULL;
	options = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == STR)
			options++;
		else if (tmp->type != STR && tmp->type != PIPE && tmp->type != RFILE)
		{
			if (redr == 0)
			{
				cmd->redir = new_redir(tmp, colec);
				redr = 1;
			}
			else
				add_redir(cmd->redir, tmp, colec);
		}
		tmp = tmp->next;
	}
	cmd->options = _malloc(sizeof(char *) * (options + 1));
	ft_collectore(&colec, cmd->options);
	tmp = list;
	options = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == STR)
		{
			cmd->options[options] = ft_strdup(tmp->token);
			options++;
		}
		tmp = tmp->next;
	}
	cmd->options[options] = NULL;
	if (tmp)
		cmd->next = init_command(tmp->next, colec);
	else
		cmd->next = NULL;
	return (cmd);
}
