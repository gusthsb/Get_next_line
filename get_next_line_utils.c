/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustde-s <gustde-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:31:39 by gustde-s          #+#    #+#             */
/*   Updated: 2026/07/20 17:27:05 by gustde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t count)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (count == 0)
		return (src_len);
	while (src[i] != '\0' && i < count - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	j;

	dest_len = 0;
	src_len = 0;
	j = 0;
	while (dest[dest_len] != '\0')
		dest_len++;
	while (src[src_len] != '\0')
		src_len++;
	if (size <= dest_len)
		return (size + src_len);
	while (src[j] != '\0' && dest_len + j < size - 1)
	{
		dest[dest_len + j] = src[j];
		j++;
	}
	dest[dest_len + j] = '\0';
	return (dest_len + src_len);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	len_strs;
	char	*memaloc;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	len_strs = ft_strlen(s1) + (ft_strlen(s2) + 1);
	memaloc = (char *)malloc(len_strs);
	if (!memaloc)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(memaloc, s1, ft_strlen(s1) + 1);
	ft_strlcat(memaloc, s2, len_strs);
	free(s1);
	return (memaloc);
}
