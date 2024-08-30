/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:59:32 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/30 04:24:10 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	env_free(t_env **node)
{
	t_env	*tmp;
	t_env	*cur;

	if (!node || !*node)
		return ;
	cur = *node;
	while (cur)
	{
		tmp = cur->next;
		if (cur->line[0])
		{
			free(cur->line[0]);
			cur->line[0] = NULL;
		}
		if (cur->line[1])
		{
			free(cur->line[1]);
			cur->line[1] = NULL;
		}
		free(cur);
		cur = tmp;
	}
	*node = NULL;
}

static void	delete_node(t_env **env, t_env *delnode, t_env *prev)
{
	t_env	*node;

	if (!delnode)
		return ;
	node = delnode->next;
	if (prev)
		prev->next = node;
	else
		*env = node;
	delnode->next = NULL;
	env_free(&delnode);
}

static void	env_delete(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*pev;

	pev = NULL;
	if (!env || !*env || !str || !*str)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line[0], str, ft_strlen(str)))
		{
			delete_node(env, tmp, pev);
			tmp = *env;
		}
		else
		{
			pev = tmp;
			tmp = tmp->next;
		}
	}
}

void	ft_unset(t_command *cmd, t_env **env, int *ex)
{
	int	i;

	i = 1;
	if (!cmd || !env || !*env)
		return ;
	if (!cmd->options[1])
		return ;
	while (cmd->options[i])
	{
		env_delete(env, cmd->options[i]);
		i++;
	}
	*ex = 0;
}
