/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 05:14:41 by bamssaye          #+#    #+#             */
/*   Updated: 2023/11/25 00:19:55 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lens;
	char	*str;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start > lens)
		len = 0;
	else if (len + start > lens)
		len = lens - start;
	str = (char *)malloc((len * sizeof(char)) + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}
