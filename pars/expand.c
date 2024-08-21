/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:41 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/21 15:34:52 by amousaid         ###   ########.fr       */
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
				if (s[i] == c && quote == '\"')
				{
					*flag = 1;
					return (&s[i]);
				}
				i++;
			}
			if (s[i] == quote)
				i++;
		}
		else if (s[i] == c)
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
		new_data[x] = ft_strjoin("\"", tmp2_2[j]);
		new_data[x] = ft_strjoin(new_data[x], "\"");
		x++;
		j++;
	}
	i++;
	complete_tab(new_data, tab, x, i);
	free(tab);
	free(tmp2_2);
	return (new_data);
}
char	*ft_strjoinss(char *s1, char *s2)
{
	char	*str;
	size_t	ls1;
	size_t	ls2;
	size_t	t;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	t = ls1 + ls2 + 1;
	str = ft_calloc(t, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ls1);
	ft_memcpy(str + ls1, s2, ls2);
	free (s1);
	return (str);
}

char	**ft_expand(char **tab, t_main *mini)
{
	char	**tmp2_2;
	int		i;
	int		j;
	int		flag;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	// (void)mini;
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (dstrchr(tab[i], '$', &flag) && (i == 0 || is_type(tab[i - 1]) == RFILE
				|| is_type(tab[i - 1]) == PIPE || is_type(tab[i - 1]) == STR))
		{
			while (tab[i] && dstrchr(tab[i], '$', &flag))
			{
				tmp2 = dstrchr(tab[i], '$', &flag);
				j++;
				if (tmp2[j] && tmp2[j] == '?')
				{
					expand_exit_s(tab, i, mini, tmp2);
					j = 0;
					continue ;
				}
				tmp3 = ft_substr(tab[i], 0, tmp2 - tab[i]);
				while (tmp2[j] && (ft_isalnum(tmp2[j]) || tmp2[j] == '_')
					&& !ft_isdigit(tmp2[1]))
					j++;
				if (!ft_isalpha(tmp2[1]) && tmp2[1] != '_' && j == 1)
					j++;
				tmp = &tmp2[j];
				tmp2 = ft_substr(tmp2 + 1, 0, j - 1);
				if (getmyenv(mini->env, tmp2))
					tmp3 = ft_strjoinss(tmp3, getmyenv(mini->env, tmp2));
				tmp3 = ft_strjoinss(tmp3, tmp);
				// printf("tmp3 = %c\n", tmp3[ft_strlen(tmp3) - 1]);
				//this doesn't work
				free (tmp2);
				if (flag == 1 || tmp3[ft_strlen(tmp3) - 1] == '$')
				{
					free(tab[i]);
					tab[i] = tmp3;
				}
				else if (flag == 2)
				{
					tmp2_2 = ft_split(tmp3);
					if (d2_len(tmp2_2) > 1)
					{
						tab = resize_tab(tab, tmp2_2, i);
						free(tmp3);
					}
					else
					{
						free(tab[i]);
						tab[i] = tmp3;
					}
					arry_c(tmp2_2);
				}
				j = 0;
			}
		}
		j = 0;
		i++;
	}
	//
	return (tab);
}
