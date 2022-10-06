/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 21:58:55 by aperol-h          #+#    #+#             */
/*   Updated: 2021/08/05 12:53:18 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t		c;

	c = 0;
	while (s[c] != 0)
		c++;
	return (c);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (1)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		if (!*s++)
			break ;
	}
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	register const char	*firsts;
	register char		*firstd;
	register const char	*lasts;
	register char		*lastd;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		firsts = (const char *) src;
		firstd = (char *) dest;
		while (n--)
			*firstd++ = *firsts++;
	}
	else
	{
		lasts = (const char *)src + (n - 1);
		lastd = (char *)dest + (n - 1);
		while (n--)
			*lastd-- = *lasts--;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	size1;
	size_t	size2;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	newstr = (char *)malloc((size1 + size2 + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_memmove(newstr, s1, size1);
	ft_memmove(newstr + size1, s2, size2);
	newstr[size1 + size2] = '\0';
	return (newstr);
}

char	*ft_strdup(char *src)
{
	char		*ptr;
	size_t		size;
	int			i;

	if (src == (char *)1)
		return (NULL);
	size = ft_strlen(src) + 1;
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (src[i] != 0)
	{
		ptr[i] = src[i];
		i++;
	}
	if (src[i] == 0)
		ptr[i] = '\0';
	return (ptr);
}
