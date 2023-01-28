/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraqioui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:15:11 by fraqioui          #+#    #+#             */
/*   Updated: 2023/01/21 10:15:12 by fraqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	s1_l;
	size_t	s2_l;
	size_t	i;
	size_t	j;

	if (!(s1 || s2))
		return (0);
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	i = 0;
	j = 0;
	while (i <= s1_l && j <= s2_l && n--)
	{
		if (s1[i] != s2[j])
			return ((unsigned char) s1[i] - s2[j]);
		i++;
		j++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	char	*end;

	end = (char *)s;
	while (*end)
		end++;
	return (end - s);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_s = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_s)
		return (NULL);
	ft_memcpy(new_s, s1, s1_len);
	ft_memcpy(new_s + s1_len, s2, s2_len);
	new_s[s2_len + s1_len] = '\0';
	return (new_s);
}

int	ft_search(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}
