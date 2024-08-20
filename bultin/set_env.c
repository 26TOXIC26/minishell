/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 03:59:28 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/20 04:35:50 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_lstl(t_env *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

void	ft_lst_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstl(*lst);
	last->next = new;
}
t_env	*ft_lstn(char *a, char *b, int type)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->line[0] = ft_strdup(a);
    node->line[1] = ft_strdup(b);
	node->exp = type;
	node->next = NULL;
	return (node);
}
t_env *s_env_empty()
{
    t_env	    *lst;
	t_env	    *new;
    char        *tmp;
    // m->env[0] = ft_strjoin("PWD=", tmp);
		// free(tmp);
		// m->env[1] = ft_strdup("");
		// m->env[2] = ft_strdup("_=/usr/bin/env");
		// m->env[3] = NULL;
    lst = NULL;
    tmp = getcwd(NULL, 0);
    new = ft_lstn("PWD", tmp, 0);
    ft_lst_back(&lst, new);
    ft_lst_back(&lst, ft_lstn("SHLVL", "1", 0));
    ft_lst_back(&lst, ft_lstn("_", "/usr/bin/env", 0));
    free(tmp);
    return (lst);   
}
t_env *set_envc(char **env)
{
    t_env	*lst;
	t_env	*new;
	int		i;
	char	*str;
	char	**line;

	lst = NULL;
	if (!env || !*env)
		return (s_env_empty());
	else
	{
		i = 0;
		while (env[i])
		{
			str = ft_strdup(env[i]);
			line = ft_split1(str, '=');
			new = ft_lstn(line[0], line[1], 0);
			ft_lst_back(&lst, new);
			free(str);
			i++;
		}
	}
	return (lst);
}
