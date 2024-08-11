/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:29:37 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/11 22:28:37 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
char	*dup_line(const char *aux)
{
	char	*duplicate;
	size_t	i;

	duplicate = (char *)malloc((strlen_gnl(aux) + 1) * (sizeof(char)));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (aux[i])
	{
		duplicate[i] = aux[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

/*					like strjoin 		*/
char	*join_line(char const *line, char const *buffer)
{
	char	*aux;
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
	aux = (char *)malloc((len_joined + 1) * sizeof(char));
	if (!aux)
		return (NULL);
	aux[len_joined] = '\0';
	aux = memcpy_line(aux, line, len_line);
	aux = memcpy_line(&aux[len_line], buffer, len_buffer);
	return (aux-len_line);
}
