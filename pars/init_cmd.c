/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:27:55 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/18 12:09:12 by codespace        ###   ########.fr       */
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

void	init_rnode(t_list *tmp, t_colec *colec, t_command *cmd, int *options)
{
	int	redr;

	redr = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == STR)
			(*options)++;
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
}

t_list	*init_options(t_list *list, t_command *cmd, int *options)
{
	t_list	*tmp2;

	tmp2 = list;
	while (tmp2 && tmp2->type != PIPE)
	{
		if (tmp2->type == STR)
		{
			cmd->options[*options] = ft_strdup(tmp2->token);
			(*options)++;
		}
		tmp2 = tmp2->next;
	}
	cmd->options[*options] = NULL;
	return (tmp2);
}

t_command	*init_command(t_list *list, t_colec *colec)
{
	t_command	*cmd;
	t_list		*tmp;
	int			options;

	tmp = list;
	cmd = _malloc(sizeof(t_command));
	ft_collectore(&colec, cmd);
	cmd->redir = NULL;
	options = 0;
	init_rnode(tmp, colec, cmd, &options);
	cmd->options = _malloc(sizeof(char *) * (options + 1));
	ft_collectore(&colec, cmd->options);
	options = 0;
	tmp = init_options(list, cmd, &options);
	if (tmp)
		cmd->next = init_command(tmp->next, colec);
	else
		cmd->next = NULL;
	return (cmd);
}
