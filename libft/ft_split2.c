/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:14:19 by amousaid          #+#    #+#             */
/*   Updated: 2024/07/30 21:38:05 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_wordcount2(char const *s, int *i, int *count)
{
	while (s[*i])
	{
		if (s[*i] == ' ' || (s[*i] >= 9 && s[*i] <= 13))
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
			(*i)++;
			(*count)++;
		}
		else
		{
			(*count)++;
			while (s[*i] && s[*i] != ' ' && !(s[*i] >= 9 && s[*i] <= 13))
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
