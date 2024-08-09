/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:29:37 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/09 20:52:22 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

strlen_gnl//like strlen

void	*memcpy_line(void *dest, const void *src, size_t len)//	like mempcy
{
	const char	*src_ptr;
	char		*dest_ptr;
	size_t		i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	dest_ptr = (unsigned char *) dest;
	src_ptr = (const unsigned char *) src;
	while (i < len)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}

char	*dup_line(const char *aux)//		like strdup
{
	char	*duplicate;
	size_t	i;

	duplicate = (char *)malloc(strlen_gnl(aux) + 1) * (sizeof(char));
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

char	*join_line(char const *line, char const *buffer)//	like strjoin
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
	while (len_line -- > 0)
		aux--;
	return (aux);
}
