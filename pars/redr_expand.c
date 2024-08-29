/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 00:59:12 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/29 20:23:00 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	do_her_expand(t_expand *e, t_main *m, char *result)
{
	e->result = ft_substr(result, 0, e->e_str - result);
	while (e->e_str[e->j] && (ft_isalnum(e->e_str[e->j])
			|| e->e_str[e->j] == '_') && !ft_isdigit(e->e_str[1]))
		e->j++;
	if (e->j == 1 && ft_isdigit(e->e_str[e->j]))
		e->j++;
	e->complet = &e->e_str[e->j];
	e->e_str = ft_substr(e->e_str + 1, 0, e->j - 1);
	if (getmyenv(m->env, e->e_str))
		e->result = strjoing_f1(e->result, getmyenv(m->env, e->e_str));
	e->len = ft_strlen(e->result);
	e->result = strjoing_f1(e->result, e->complet);
	if ((e->result[e->len] == '\"' || e->result[e->len] == '\'')
		&& e->result[e->len + 1] && !check_quote1(e->result + e->len))
		e->len++;
}

char	*her_expand(char *str, t_main *m)
{
	char		*result;
	t_expand	e;

	result = ft_strdup(str);
	e.i = 0;
	e.last_c = result;
	while (e.last_c && ft_strchr(e.last_c, '$'))
	{
		e.j = 0;
		e.e_str = ft_strchr(e.last_c, '$');
		e.j++;
		if (e.e_str[e.j] && e.e_str[e.j] == '?')
		{
			expand_exit_s(&result, m, &e);
			continue ;
		}
		do_her_expand(&e, m, result);
		free(result);
		result = e.result;
		e.last_c = result + e.len;
		free(e.e_str);
	}
	return (result);
}

char	*redir_expand(char *file, t_main *m, int *flag)
{
	char	*result;
	t_expand	e;

	result = ft_strdup(file);
	e.j = 0;
	e.last_c = result;
	while (e.last_c && dstrchr(e.last_c, '$', &e.flag))
	{
		e.e_str = dstrchr(e.last_c, '$', &e.flag);
		e.j++;
		if (e.e_str[e.j] && e.e_str[e.j] == '?')
		{
			expand_exit_s(&result, m, &e);
			continue ;
		}
		e.result = ft_substr(result, 0, e.e_str - result);
		while (e.e_str[e.j] && (ft_isalnum(e.e_str[e.j])
				|| e.e_str[e.j] == '_') && !ft_isdigit(e.e_str[1]))
			e.j++;
		if (e.j == 1 && ft_isdigit(e.e_str[e.j]))
			e.j++;
		e.complet = &e.e_str[e.j];
		e.e_str = ft_substr(e.e_str + 1, 0, e.j - 1);
		if (e.flag == 2 && (!getmyenv(m->env, e.e_str) || !check_space(getmyenv(m->env, e.e_str))))
		{
			*flag = 1;
			(free(e.result)), (free(e.e_str)), (free(result));
			return (ft_strdup(file));
		}
		else if (getmyenv(m->env, e.e_str))
			e.result = strjoing_f1(e.result, getmyenv(m->env, e.e_str));
		e.len = ft_strlen(e.result);
		e.result = strjoing_f1(e.result, e.complet);
		if ((e.result[e.len] == '\"' || e.result[e.len] == '\'')
			&& e.result[e.len + 1] && !check_quote1(e.result + e.len))
			e.len++;
		free(result);
		result = e.result;
		e.last_c = result + e.len;
		free(e.e_str);
	}
	return (result);
}
