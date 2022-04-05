/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:18:41 by                   #+#    #+#             */
/*   Updated: 2021/10/21 18:28:46 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line_bonus.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	i = -1;
	s2 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (s2 == NULL)
		return (0);
	while (s1 && s1[++i])
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (0);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	i = -1;
	ch = (unsigned char) c;
	if (ch == 0)
		return ((char *) &s[ft_strlen(s)]);
	while (s[++i])
		if (s[i] == ch)
			return ((char *) &s[i]);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}
