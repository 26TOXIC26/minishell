/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 05:14:06 by bamssaye          #+#    #+#             */
/*   Updated: 2024/06/06 19:34:11 by abdelilah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			i++;
		else if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			if (s[i-1] == '\'')
				while (s[i] != '\'')
					i++;
			else
				while (s[i] != '\"')
					i++;
			i++;
			count++;
		}
		else
		{
			count++;
			while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
				i++;
		}
	}
	return (count);
}

static char	**ft_freespace(char **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	*ft_setword(char *stri, char const *s, int j, int wordlen)
{
	int	i;

	i = 0;
	while (wordlen > 0)
	{
		stri[i] = s[j - wordlen];
		i++;
		wordlen--;
	}
	stri[i] = '\0';
	return (stri);
}

static char	**ft_splitall(char **str, char const *s, int countword)
{
	int	i;
	int	j;
	int	wordlen;

	i = 0;
	j = 0;
	while (s[i] && j < countword)
	{
		wordlen = 0;
		while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			wordlen++;
			if (s[i-1] == '\'')
				while (s[i] != '\'')
				{
					wordlen++;	
					i++;
				}
			else
				while (s[i] != '\"')
				{
					wordlen++;
					i++;
				}
			i++;
			wordlen++;
		}
		else
		{
			while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
			{
				i++;
				wordlen++;
			}
		}
		str[j] = malloc((wordlen + 1) * sizeof(char));
		if (!str[j])
			return (ft_freespace(str, countword));
		ft_setword(str[j], s, i, wordlen);
		j++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s)
{
	int		countword;
	char	**str;

	if (!s)
		return (NULL);
	countword = ft_wordcount(s);
	str = malloc((countword + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	ft_splitall(str, s, countword);
	return (str);
}
// #include <stdio.h>
// int main()
// {
// 	char p[] = "    hello dear ou need     ";
// 	char **c = ft_split(p, ' ');
// 	int i = 0;
// 	while(c[i])
// 		printf("%s \n", c[i++]);
// 	ft_freespace(c,i);
// }