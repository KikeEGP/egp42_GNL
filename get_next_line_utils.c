/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:29:37 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/18 18:48:28 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>//DELETE THISSSS !!!!!!

/*					like strlen		*/
size_t	strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*					like memcpy 		*/
void	*memcpy_line(void *dest, const void *src, size_t len)
{
	const char	*src_ptr;
	char		*dest_ptr;
	size_t		i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	dest_ptr = (char *) dest;
	src_ptr = (const char *) src;
	while (i < len)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}

/*					like strdup 		*/
char	*dup_line(const char *line)
{
	char	*duplicate;
	size_t	i;

	duplicate = (char *)malloc((strlen_gnl(line) + 1) * (sizeof(char)));
	if (!duplicate)
		return (NULL);
	i = 0;
	duplicate[i] = '\0';
	while (line[i])
	{
		duplicate[i] = line[i];
		i++;
	}
	return (duplicate);
}

/*					like strjoin 		*/
char	*join_line(char const *line, char const *buffer)
{
	char	*new;
	size_t	len_line;
	size_t	len_buffer;
	size_t	len_joined;

	if (!buffer)
		return (NULL);
	if (!line && buffer)
		return (dup_line(buffer));
	len_line = strlen_gnl(line);
	len_buffer = strlen_gnl(buffer);
	len_joined = len_line + len_buffer;
	new = (char *)malloc((len_joined + 1) * sizeof(char));
	if (!new)
		return (NULL);
	new[len_joined] = '\0';
	new = memcpy_line(new, line, len_line);
	new = memcpy_line(&new[len_line], buffer, len_buffer);
	return (new - len_line);
}
