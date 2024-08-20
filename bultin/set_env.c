/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 03:59:28 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/20 18:06:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// t_env	*ft_lstl(t_env *token)
// {
// 	if (!token)
// 		return (NULL);
// 	while (token->next)
// 		token = token->next;
// 	return (token);
// }

// void	ft_lst_back(t_env **lst, t_env *new)
// {
// 	t_env	*last;

// 	if (!new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last = ft_lstl(*lst);
// 	last->next = new;
// }
// t_env	*ft_lstn(char *a, char *b, int type)
// {
// 	t_env	*node;

// 	node = malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node->line[0] = ft_strdup(a);
//     node->line[1] = ft_strdup(b);
// 	node->exp = type;
// 	node->next = NULL;
// 	return (node);
// }
// t_env *s_env_empty()
// {
//     t_env	    *lst;
// 	t_env	    *new;
//     char        *tmp;

//     lst = NULL;
//     tmp = getcwd(NULL, 0);
//     new = ft_lstn("PWD", tmp, 0);
//     ft_lst_back(&lst, new);
//     ft_lst_back(&lst, ft_lstn("SHLVL", "1", 0));
//     ft_lst_back(&lst, ft_lstn("_", "/usr/bin/env", 0));
//     free(tmp);
//     return (lst);   
// }
// void change_shlvl(char *str)
// {
//     int i;
//     char *tmp;

//     i = ft_atoi(str);
//     i++;
//     tmp = ft_itoa(i);
//     ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
// 	free(tmp);
// }
// t_env *set_envc(char **env)
// {
//     t_env	*lst;
// 	t_env	*new;
// 	int		i;
// 	char	*str;
// 	char	**line;

// 	lst = NULL;
// 	if (!env || !*env)
// 		return (s_env_empty());
// 	else
// 	{
// 		i = 0;
// 		while (env[i])
// 		{
// 			str = ft_strdup(env[i]);
// 			line = ft_split1(str, '=');
//             if (!ft_strncmp(line[0],"SHLVL", 5))
//                     change_shlvl(line[1]);
// 			new = ft_lstn(line[0], line[1], 0);
// 			ft_lst_back(&lst, new);
// 			free(str);
// 			i++;
// 		}
// 	}
// 	return (lst);
// }

t_env *creat_new_env(char *str)
{
	t_env	*new;
	
	char	*f_line;
	char	*s_line;

	s_line = ft_strchr(str, '=') + 1;
	f_line = ft_substr(str, 0, s_line - str - 1);
	new = _malloc(sizeof(t_env));
	new->line[0] = f_line;
	new->line[1] = s_line;
	new->exp = 0;
	new->index = 0;
	new->next = NULL;
	return (new);
}

void ft_env_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_env *new_env(void)
{
	t_env	*new;

	new = creat_new_env(ft_strjoin("PWD=", getcwd(NULL, 0)));
	ft_env_back(&new, creat_new_env("SHLVL=1"));
	ft_env_back(&new, creat_new_env("_=/usr/bin/env"));
	return (new);
}

t_env	*set_envc(char **env)
{
	int		i;
	t_env	*new;
	t_env	*envs;

	i = 0;
	if (!env || !*env)
		return (new_env());
	envs = creat_new_env(env[i]);
	i++;
	while (env[i])
	{
		new = creat_new_env(env[i]);
		ft_env_back(&envs, new);
		i++;
	}
	return (envs);
}

// int main(int ac, char **av, char **env)
// {
// 	t_env	*envs;

// 	(void)ac;
// 	(void)av;
// 	envs = set_envc(env);
// 	while (envs)
// 	{
// 		printf("%s=\"%s\"\n", envs->line[0], envs->line[1]);
// 		envs = envs->next;
// 	}
// 	return (0);
// }
