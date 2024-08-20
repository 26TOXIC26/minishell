/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:55:25 by abdelilah         #+#    #+#             */
/*   Updated: 2024/08/20 02:57:09 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_env(char *str, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	len = i;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, len) && (env[i][len] == '='
			|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	plus_shlvl(size_t i, t_minishell *mini)
{
	char	*str;
	char	*tmp;
	int		j;

	str = ft_strchr(mini->env[i], '=') + 1;
	j = ft_atoi(str);
	j++;
	tmp = ft_itoa(j);
	ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
	free(tmp);
}

char	**ft_init(char **env)
{
	int		i;
	int		len;
	char	**tmp;
	size_t	l;

	i = 0;
	while (env[i])
		i++;
	tmp = _malloc((i + 1) * sizeof(char *));
	tmp[i] = NULL;
	len = i;
	i = 0;
	while (i < len)
	{
		l = ft_strlen(env[i]);
		tmp[i] = malloc(sizeof(char) * l + 1);
		ft_strlcpy(tmp[i], env[i], l + 1);
		i++;
	}
	return (tmp);
}
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
	node->line = _malloc(sizeof(char *) * 3);
	node->line[0] = ft_strdup(a);
	node->line[1] = ft_strdup(b);
	node->line[2] = NULL;
	node->exp = type;
	node->next = NULL;
	return (node);
}

void	set_env(t_env **envs, char **env)
{
	// char *tmp;
	t_env *node;
	// (void)m;
	(void)env;
	*envs = ft_lstn("SHLVL", "lkl1", 0);
	node = ft_lstn("PWD", "tmp", 0);
	ft_lst_back(envs, node);
	// if (!*env || !env)
	// {
		// tmp = getcwd(NULL, 0);
		// m->env = _malloc(sizeof(char *) * 4);
		// m->env[0] = ft_strjoin("PWD=", tmp);
		// free(tmp);
		// m->env[1] = ft_strdup("SHLVL=1");
		// m->env[2] = ft_strdup("_=/usr/bin/env");
		// m->env[3] = NULL;
		// node = ft_lstn("SHLVL", "1", 0);
		// m->envs = ft_lstn("PWD", "tmp", 0);
		// ft_lst_back(&m->envs, node);
		// ft_lst_back(&m->envs, ft_lstn("_", "/usr/bin/env", 0));
		// free(tmp);
		
		//m->envs->line = _malloc(sizeof(char *) * 4);
		
		// envs = node;
























		
	// }
	// else
	// {
	// 	m->env = ft_init(env);
	// 	plus_shlvl(find_env("SHLVL", m->env), m);
	// }
}
