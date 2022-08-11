/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:29:22 by                   #+#    #+#             */
/*   Updated: 2021/10/07 20:26:13 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
