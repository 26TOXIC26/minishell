/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <bamssaye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 03:18:00 by pc                #+#    #+#             */
/*   Updated: 2024/09/03 14:24:43 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (perror("malloc"), exit(1), NULL);
	return (ptr);
}

int	d2_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*strdup_limit(const char *str, int limit)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] && i < limit)
		i++;
	ptr = malloc(sizeof(char) * i + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (str[i] && i < limit)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	check_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

char	*strjoing_f1(char *s1, char *s2)
{
	char	*str;
	size_t	ls1;
	size_t	ls2;
	size_t	t;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	t = ls1 + ls2 + 1;
	str = ft_calloc(t, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ls1);
	ft_memcpy(str + ls1, s2, ls2);
	free(s1);
	return (str);
}
