/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 05:14:06 by bamssaye          #+#    #+#             */
/*   Updated: 2024/08/28 23:10:31 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcounts(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**arry_c(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
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

static char	**ft_splitall(char **str, char const *s, char c, int countword)
{
	int	i;
	int	j;
	int	wordlen;

	i = 0;
	j = 0;
	while (s[i] && j < countword)
	{
		wordlen = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			wordlen++;
		}
		str[j] = malloc((wordlen + 1) * sizeof(char));
		if (!str[j])
			return (arry_c(str));
		ft_setword(str[j], s, i, wordlen);
		j++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split1(char const *s, char c)
{
	int		countword;
	char	**str;

	if (!s)
		return (NULL);
	countword = ft_wordcounts(s, c);
	str = malloc((countword + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	ft_splitall(str, s, c, countword);
	return (str);
}
