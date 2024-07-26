/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:41 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/16 04:48:53 by abdelilah        ###   ########.fr       */
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
		new_data[x] = ft_strdup(tmp2_2[j]);
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

void	ft_dsymbol(char **tab, t_minishell *mini)
{
	char	*tmp;
	char	*tmp2;
	// char	**tmp2_2;
	(void)mini;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		while (tab[i][j] && dstrchr(tab[i] + j, '$'))
		{
			tmp = dstrchr(tab[i] + j, '$');
			if (tmp && (i == 0 || is_type(tab[i - 1]) != HEREDOC))
			{
				while (tmp && tmp[j] && (ft_isalnum(tmp[j])
					|| tmp[j] == '_'))
					j++;
				tmp2 = ft_substr(tab[i], 0, tmp - tab[i]);
				if (getmyenv(mini, ft_substr(tab[i], tmp - tab[i] + 1, j)))
					tmp2 = ft_strjoin(tmp2, getmyenv(mini, tmp + 1));
				tmp2 = ft_strjoin(tmp2, tmp + 1 + ft_strlen(getmyenv(mini, tmp + 1)));
				free(tab[i]);
				tab[i] = tmp2;
				printf("tmp2 = %s\n", tab[i]);
			}
		}
		j = 0;
		i++;
	}
}
				// if (tmp[0] == '\"')
				// {
				// 	free(tab[i]);
				// 	tab[i] = tmp;
				// }
				// else
				// {
				// 	tmp2_2 = ft_split(tmp);
				// 	if (d2_len(tmp2_2) > 1)
				// 	{
				// 		tab = resize_tab(tab, tmp2_2, i);
				// 		free(tmp);
				// 	}
				// 	else
				// 	{
				// 		free(tab[i]);
				// 		tab[i] = tmp;
				// 	}
				// }
