/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelilah <abdelilah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 05:14:06 by bamssaye          #+#    #+#             */
/*   Updated: 2024/06/08 19:57:17 by abdelilah        ###   ########.fr       */
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
			printf("i = %d\n", i);
			if (s[i-1] == '\'')
				while (s[i] && s[i] != '\'')
					i++;
			else
				while (s[i] && s[i] != '\"')
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

char *set_word(char *word, char const *s, int *i)
{
	int j = 0;
	while (s[*i] && s[*i] != ' ' && !(s[*i] >= 9 && s[*i] <= 13))
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			(*i)++;
			if (s[*i-1] == '\'')
				while (s[*i] != '\'')
				{
					word[j] = s[*i];
					j++;
					(*i)++;
				}
			else
				while (s[*i] != '\"')
				{
					word[j] = s[*i];
					j++;
					(*i)++;
				}
			(*i)++;
		}
		else
		{
			word[j] = s[*i];
			j++;
			(*i)++;
		}
	}
	word[j] = '\0';
	return (word);
}

int ft_word_len(char *s, int i)
{
	int wordlen = 0;
	if (s[i] == '\'' || s[i] == '\"')
	{
		i++;
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
	}
	else
	{
		while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
		{
			i++;
			wordlen++;
		}
	}
	return (wordlen);
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
		while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i++;
		wordlen = ft_word_len((char *)s, i);
		str[j] = malloc((wordlen + 1) * sizeof(char));
		if (!str[j])
			return (ft_freespace(str, countword));
		set_word(str[j], s, &i);
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

//ls 'ls ' "ls"ls ' ' heklklo