/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:41 by amousaid          #+#    #+#             */
/*   Updated: 2024/09/06 11:18:20 by bamssaye         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (s && s[i])
	{
		if ((s[i] == '\"' && ft_strchr(&s[i + 1], '\"')) || s[i] == '\''
			|| !in_quotes(s, (ft_strlen(s) - 1), c))
		{
			if (s[i] != '\"' && s[i] != '\'')
			{
				while (s[i] && s[i] != c && s[i] != '\"')
					i++;
				if (s[i] == c)
					return (*flag = 1, &s[i]);
			}
			else if (dstrchr2(s, c, &i))
				return (*flag = 1, &s[i]);
		}
		else if (s[i] == c)
			return (*flag = 2, &s[i]);
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
	arry_c(tab);
	return (new_data);
}

char	**ft_expand(char **tab, t_main *mini)
{
	t_expand	e;

	e.i = 0;
	while (tab[e.i])
	{
		e.j = 0;
		if (dstrchr(tab[e.i], '$', &e.flag) && (e.i == 0 || is_type(tab[e.i
						- 1]) == RFILE || is_type(tab[e.i - 1]) == PIPE
				|| is_type(tab[e.i - 1]) == STR))
		{
			e.last_c = tab[e.i];
			while (e.last_c && dstrchr(e.last_c, '$', &e.flag))
			{
				e.e_str = dstrchr(e.last_c, '$', &e.flag);
				e.j++;
				if (do_expand(&e, &tab, mini) == 0)
					break ;
				else
					continue ;
			}
		}
		e.i++;
	}
	return (tab);
}
