/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustde-s <gustde-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:31:36 by gustde-s          #+#    #+#             */
/*   Updated: 2026/07/20 17:16:35 by gustde-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*keep_read(int fd, char *remainder)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(remainder, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(remainder);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		remainder = ft_strjoin(remainder, buffer);
	}
	free(buffer);
	return (remainder);
}

char	*extract_line(char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	if (!remainder || !remainder[i])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_remainder(char *remainder)
{
	int		i;
	int		j;
	char	*new_remainder;

	i = 0;
	j = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = malloc(sizeof(char) * (ft_strlen(remainder) - i + 1));
	if (!new_remainder)
	{
		free(remainder);
		return (NULL);
	}
	i++;
	while (remainder[i])
		new_remainder[j++] = remainder[i++];
	new_remainder[j] = '\0';
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = keep_read(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	remainder = update_remainder(remainder);
	return (line);
}
