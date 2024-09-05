/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 05:27:55 by amousaid          #+#    #+#             */
/*   Updated: 2024/09/05 05:58:53 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redir	*new_redir(t_list *list, t_main *mini)
{
	t_redir	*redir;
	char	*tmp;

	redir = _malloc(sizeof(t_redir));
	redir->flag = 0;
	redir->type = list->type;
	redir->file = ft_strdup(list->next->token);
	if (redir->type == HEREDOC && (ft_strchr(redir->file, '\'')
			|| ft_strchr(redir->file, '\"')))
	{
		redir->flag = 1;
		redir->file = remove_quotes2(redir->file);
	}
	else if (redir->type != HEREDOC)
	{
		tmp = redir->file;
		redir->file = redir_expand(redir->file, mini, &redir->flag);
		redir->file = remove_quotes2(redir->file);
		free(tmp);
	}
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir *redir, t_list *list, t_main *mini)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir(list, mini);
}

void	init_rnode(t_list *tmp, t_command *cmd, int *options, t_main *mini)
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
				cmd->redir = new_redir(tmp, mini);
				redr = 1;
			}
			else
				add_redir(cmd->redir, tmp, mini);
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

t_command	*init_command(t_list *list, t_main *mini)
{
	t_command	*cmd;
	t_list		*tmp;
	int			options;

	tmp = list;
	cmd = _malloc(sizeof(t_command));
	cmd->redir = NULL;
	options = 0;
	init_rnode(tmp, cmd, &options, mini);
	cmd->options = _malloc(sizeof(char *) * (options + 1));
	options = 0;
	tmp = init_options(list, cmd, &options);
	if (tmp)
		cmd->next = init_command(tmp->next, mini);
	else
		cmd->next = NULL;
	return (cmd);
}
