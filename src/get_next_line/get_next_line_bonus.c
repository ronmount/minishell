/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:16:42 by                   #+#    #+#             */
/*   Updated: 2021/10/21 20:00:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	int		i;
	char	*str;

	p = malloc(count * size);
	if (p == NULL)
		return (0);
	i = -1;
	str = (char *)p;
	size++;
	while (--size > 0)
		str[++i] = '\0';
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*join;

	j = -1;
	i = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (i + 1));
	if (join == NULL)
		return (0);
	join[i] = '\0';
	i = -1;
	while (s1[++i])
		join[++j] = s1[i];
	i = -1;
	while (s2[++i])
		join[++j] = s2[i];
	return (join);
}

char	*ft_remainder(int fd, char *remainder)
{
	ssize_t	n;
	char	*buf;
	char	*tmp;

	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (NULL);
	n = 1;
	while (n != 0 && !ft_strchr(buf, '\n'))
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[n] = '\0';
		tmp = remainder;
		if (!tmp)
			tmp = ft_strdup("");
		remainder = ft_strjoin(tmp, buf);
		free(tmp);
	}
	free(buf);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*remainder[OPEN_MAX + 1];
	char		*tmp;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (0);
	remainder[fd] = ft_remainder(fd, remainder[fd]);
	str = ft_substr(remainder[fd], 0, ft_strlen(remainder[fd])
			- ft_strlen(ft_strchr(remainder[fd], '\n')) + 1);
	tmp = remainder[fd];
	remainder[fd] = ft_substr(tmp, ft_strlen(tmp)
			- ft_strlen(ft_strchr(tmp, '\n')) + 1, ft_strlen(tmp)
			- ft_strlen(str) + 1);
	if (remainder[fd] && remainder[fd][0] == '\0')
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
	}
	free(tmp);
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
	}
	return (str);
}
