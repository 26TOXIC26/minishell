/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:14:19 by amousaid          #+#    #+#             */
/*   Updated: 2024/08/13 10:53:14 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	w_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	ft_wordcount2(char const *s, int *i, int *count)
{
	while (s[*i])
	{
		if (s[*i] && w_space(s[*i]))
			(*i)++;
		else if (s[*i] == '\'' || s[*i] == '\"')
		{
			(*i)++;
			if (s[*i - 1] == '\'')
				while (s[*i] && s[*i] != '\'')
					(*i)++;
			else
				while (s[*i] && s[*i] != '\"')
					(*i)++;
			if (s[*i] == '\'' || s[*i] == '\"')
				(*i)++;
			if ((s[*i] && w_space(s[*i])) || !s[*i])
				(*count)++;
		}
		else
		{
			(*count)++;
			while (s[*i] && !w_space(s[*i]))
				(*i)++;
		}
	}
}

int	ft_wordcount(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	ft_wordcount2(s, &i, &count);
	return (count);
}

void	set_word2(char *word, char const *s, int *i, int *j)
{
	word[*j] = s[*i];
	(*j)++;
	(*i)++;
	if (s[*i - 1] == '\'')
	{
		while (s[*i] != '\'')
		{
			word[*j] = s[*i];
			(*j)++;
			(*i)++;
		}
	}
	else
	{
		while (s[*i] != '\"')
		{
			word[*j] = s[*i];
			(*j)++;
			(*i)++;
		}
	}
	word[*j] = s[*i];
	(*j)++;
	(*i)++;
}

char	*set_word(char *word, char const *s, int *i)
{
	int	j;

	j = 0;
	while (s[*i] && s[*i] != ' ' && !(s[*i] >= 9 && s[*i] <= 13))
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			set_word2(word, s, i, &j);
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
