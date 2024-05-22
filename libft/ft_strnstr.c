/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamssaye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 04:37:29 by bamssaye          #+#    #+#             */
/*   Updated: 2023/11/25 11:38:03 by bamssaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lenli;

	lenli = ft_strlen(little);
	if (!lenli)
	{
		return ((char *)big);
	}
	while (*big && len >= lenli)
	{
		if ((*big == *little) && !ft_strncmp(big, little, lenli))
		{
			return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
// #include<string.h>
// #include<stdio.h>
// #include <bsd/string.h>
// int main()
// {
// 	char p[50] = "hello wrold";
// 	char *m = "";
// 	//printf("newMe:%s||| \n",ft_strnstr(NULL,"", 1));
// 	printf("new:%s||| \n",strnstr(NULL,NULL, 0));

// }
