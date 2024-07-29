/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:41 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/29 22:36:37 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*getmyenv(t_minishell *mini, char *str)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], str, ft_strlen(str)) == 0)
			if (mini->env[i][ft_strlen(str)] == '=')
				return (mini->env[i] + ft_strlen(str) + 1);
		i++;
	}
	return (NULL);
}

char	*dstrchr(char *s, char c)
{
	static int	quote;
	int			i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			quote = 1;
			i++;
			while (s[i] && s[i] != '\"')
			{
				if (s[i] == c && s[i + 1] && s[i + 1] != c && s[i + 1] != '\"')
					return (s + i);
				i++;
			}
			quote = 0;
		}
		else if (s[i] == '\'' && !quote)
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			i++;
		}
		else if (s[i] == c && s[i + 1] && (ft_isalnum(s[i + 1]) || s[i
				+ 1] == '_'))
			return (s + i);
		i++;
	}
	quote = 0;
	return (NULL);
}

char	**resize_tab(char **tab, char **tmp2_2, int i)
{
	int		x;
	int		j;
	char	**new_data;

	x = 0;
	j = 0;
	new_data = malloc(sizeof(char *) * (d2_len(tab) + d2_len(tmp2_2) + 1));
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
	while (tab[i])
	{
		new_data[x] = ft_strdup(tab[i]);
		x++;
		i++;
	}
	new_data[x] = NULL;
	free(tab);
	free(tmp2_2);
	return (new_data);
}

char	**ft_dsymbol(char **tab, t_minishell *mini)
{
	char	**tmp2_2;
	int		i;
	int		j;
	char *tmp, *tmp2, *tmp3;

	(void)mini;
	i = 0;
	j = 0;
	while (tab[i])
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		if (dstrchr(tab[i], '$') && (i == 0 || is_type(tab[i - 1]) == RFILE
				|| is_type(tab[i - 1]) == PIPE || is_type(tab[i - 1]) == STR))
		{
			while (tab[i] && dstrchr(tab[i], '$'))
			{
				tmp2 = dstrchr(tab[i], '$');
				j++;
				tmp3 = ft_substr(tab[i], 0, tmp2 - tab[i]);
				while (tmp2[j] && (ft_isalnum(tmp2[j]) || tmp2[j] == '_'))
					j++;
				tmp = &tmp2[j];
				tmp2 = ft_substr(tmp2 + 1, 0, j - 1);
				if (getmyenv(mini, tmp2))
					tmp3 = ft_strjoin(tmp3, getmyenv(mini, tmp2));
				tmp3 = ft_strjoin(tmp3, tmp);
				if (tmp3[0] == '\"')
				{
					free(tab[i]);
					tab[i] = tmp3;
				}
				else
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
				}
			}
		}
		j = 0;
		i++;
	}
	return (tab);
}
