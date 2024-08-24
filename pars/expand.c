/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:41 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/24 01:06:14 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*getmyenv(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->line[0], str))
			return (tmp->line[1]);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*dstrchr(char *s, char c, int *flag)
{
	int		i;
	char	quote;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i++;
			quote = s[i - 1];
			while (s[i] && s[i] != quote)
			{
				if (s[i] == c && s[i + 1] != '\0' && quote == '\"')
				{
					*flag = 1;
					return (&s[i]);
				}
				i++;
			}
			if (s[i] == quote)
				i++;
		}
		else if (s[i] == c && s[i + 1] != '\0')
		{
			*flag = 2;
			return (&s[i]);
		}
		else
			i++;
	}
	return (NULL);
}

void	complete_tab(char **new_data, char **tab, int x, int i)
{
	while (tab[i])
	{
		new_data[x] = ft_strdup(tab[i]);
		x++;
		i++;
	}
	new_data[x] = NULL;
}

char	**resize_tab(char **tab, char **tmp2_2, int i)
{
	int		x;
	int		j;
	char	**new_data;

	x = 0;
	j = 0;
	new_data = _malloc(sizeof(char *) * (d2_len(tab) + d2_len(tmp2_2) + 1));
	while (tab[x] && x != i)
	{
		new_data[x] = ft_strdup(tab[x]);
		x++;
	}
	while (tmp2_2[j])
	{
		new_data[x] = ft_strdup(tmp2_2[j]);
		x++;
		j++;
	}
	i++;
	complete_tab(new_data, tab, x, i);
	free(tab);
	return (new_data);
}

char	**ft_expand(char **tab, t_main *mini)
{
	char		**tmp2_2;
	t_expand	e;

	e.i = 0;
	e.j = 0;
	while (tab[e.i])
	{
		if (dstrchr(tab[e.i], '$', &e.flag) && (e.i == 0 || is_type(tab[e.i
					- 1]) == RFILE || is_type(tab[e.i - 1]) == PIPE
				|| is_type(tab[e.i - 1]) == STR))
		{
			e.tmp4 = tab[e.i];
			while (e.tmp4 && dstrchr(e.tmp4, '$', &e.flag))
			{
				e.tmp2 = dstrchr(e.tmp4, '$', &e.flag);
				e.j++;
				if (e.tmp2[e.j] && e.tmp2[e.j] == '?')
				{
					expand_exit_s(tab, e.i, mini, e.tmp2);
					e.tmp4 = tab[e.i];
					e.j = 0;
					continue ;
				}
				e.tmp3 = ft_substr(tab[e.i], 0, e.tmp2 - tab[e.i]);
				while (e.tmp2[e.j] && (ft_isalnum(e.tmp2[e.j])
						|| e.tmp2[e.j] == '_') && !ft_isdigit(e.tmp2[1]))
					e.j++;
				if (!ft_isalpha(e.tmp2[1]) && e.tmp2[1] != '_' && e.j == 1)
					e.j++;
				e.tmp = &e.tmp2[e.j];
				e.tmp2 = ft_substr(e.tmp2 + 1, 0, e.j - 1);
				if (getmyenv(mini->env, e.tmp2) && (is_space(getmyenv(mini->env,
								e.tmp2)) || e.flag == 1))
					e.tmp3 = ft_strjoinss(e.tmp3, getmyenv(mini->env, e.tmp2));
				e.len = ft_strlen(e.tmp3);
				e.tmp3 = ft_strjoinss(e.tmp3, e.tmp);
				if ((e.tmp3[e.len] == '\"' || e.tmp3[e.len] == '\'')
						&& e.tmp3[e.len + 1] && !check_quote1(e.tmp3 + e.len))
					e.len++;
				if (e.flag == 1 || e.tmp2[0] == '\'' || e.tmp2[0] == '\"'
					|| (ft_strlen(e.tmp3) > 0 && e.tmp3[ft_strlen(e.tmp3)
					- 1] == '$'))
				{
					free(tab[e.i]);
					tab[e.i] = e.tmp3;
					e.tmp4 = tab[e.i] + e.len;
				}
				else if (e.flag == 2)
				{
					if (!check_space(e.tmp3))
					{
						tmp2_2 = ft_split(e.tmp3);
						tab = resize_tab(tab, tmp2_2, e.i);
						free(e.tmp3);
						arry_c(tmp2_2);
						break ;
					}
					else
					{
						free(tab[e.i]);
						tab[e.i] = e.tmp3;
						e.tmp4 = tab[e.i] + e.len;
					}
				}
				free(e.tmp2);
				e.j = 0;
			}
		}
		e.j = 0;
		e.i++;
	}
	return (tab);
}
