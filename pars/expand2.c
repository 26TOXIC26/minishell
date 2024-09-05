/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:24:18 by amousaid          #+#    #+#             */
/*   Updated: 2024/09/05 05:58:06 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand_exit_s(char **tab, t_main *mini, t_expand *e)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp3 = ft_itoa(mini->exit_status);
	tmp = ft_substr(tab[e->i], 0, e->e_str - tab[e->i]);
	tmp1 = tmp;
	tmp = ft_strjoin(tmp, tmp3);
	e->len = ft_strlen(tmp);
	tmp2 = tmp;
	tmp = ft_strjoin(tmp, e->e_str + 2);
	free(tab[e->i]);
	free(tmp3);
	free(tmp1);
	free(tmp2);
	tab[e->i] = tmp;
	e->last_c = tab[e->i] + e->len;
	e->j = 0;
	return (1);
}

int	check_quote1(char *str)
{
	int		i;
	char	q;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i];
			i++;
			while (str[i] != q && str[i])
				i++;
			if (str[i] != q)
				return (0);
		}
		i++;
	}
	return (1);
}

int	dstrchr2(char *s, char c, int *i)
{
	char	quote;

	(*i)++;
	quote = s[*i - 1];
	while (s[*i] && s[*i] != quote)
	{
		if (s[*i] == c && s[*i + 1] != '\0' && quote == '\"')
			return (1);
		(*i)++;
	}
	if (s[*i] == quote)
		(*i)++;
	return (0);
}

int	do_flag(t_expand *e, char ***tab)
{
	if (e->flag == 1 || e->e_str[0] == '\'' || e->e_str[0] == '\"')
	{
		free((*tab)[e->i]);
		(*tab)[e->i] = e->result;
		e->last_c = (*tab)[e->i] + e->len;
	}
	else if (e->flag == 2)
	{
		if (!check_space(e->result))
		{
			e->s_tab = ft_split(e->result);
			(*tab) = resize_tab((*tab), e->s_tab, e->i);
			(free(e->result)), (free(e->e_str)), (arry_c(e->s_tab));
			return (0);
		}
		else
		{
			free((*tab)[e->i]);
			(*tab)[e->i] = e->result;
			e->last_c = (*tab)[e->i] + e->len;
		}
	}
	return (1);
}

int	do_expand(t_expand *e, char ***tab, t_main *mini)
{
	e->s_tab = NULL;
	if (e->e_str[e->j] && e->e_str[e->j] == '?')
		return (expand_exit_s((*tab), mini, e));
	e->result = ft_substr((*tab)[e->i], 0, e->e_str - (*tab)[e->i]);
	while (e->e_str[e->j] && (ft_isalnum(e->e_str[e->j])
			|| e->e_str[e->j] == '_') && !ft_isdigit(e->e_str[1]))
		e->j++;
	e->complet = &e->e_str[e->j];
	e->e_str = ft_substr(e->e_str + 1, 0, e->j - 1);
	if (getmyenv(mini->env, e->e_str) && (is_space(getmyenv(mini->env,
					e->e_str)) || e->flag == 1))
		e->result = strjoing_f1(e->result, getmyenv(mini->env, e->e_str));
	e->len = ft_strlen(e->result);
	e->result = strjoing_f1(e->result, e->complet);
	if ((e->result[e->len] == '\"' || e->result[e->len] == '\'')
		&& e->result[e->len + 1] && !check_quote1(e->result + e->len))
		e->len++;
	if (!do_flag(e, tab))
		return (0);
	free(e->e_str);
	e->j = 0;
	return (1);
}
