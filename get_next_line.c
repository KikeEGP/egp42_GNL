/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/25 20:24:57 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*If buffer has chars after \n, keep for next call. Free buf, buf != next*/
static char	*next_line(char *buf)
{
	char	*next;
	char	*end;

	end = end_line(buf);
	if (end + 1)
	{
		next = dup_line(end + 1);
		if (!next)
			return (NULL);
		free(buf);
		return (next);
	}
	return (NULL);
}

/*				It's like substr to get the complete line*/
static char	*line_returned(char *kept)
{
	char	*line;
	char	*end;
	size_t	len;

	if (kept != NULL && end_line(kept))
	{
		end = end_line(kept);
		len = strlen_gnl(kept) - strlen_gnl(end);
		line = (char *)malloc((len + 1) * sizeof(char));
		if (!line)
			return (NULL);
		line[len] = '\0';
		line = memcpy_line(line, kept, len);
		return (line);
	}
	return (NULL);
}

/*Read and save line unitl \n. buf null-end == !overflow; free line in join*/
static char	*line_read(int fd, char *line)
{
	ssize_t	nb_read;
	char	*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	nb_read = 1;
	while (!end_line(buf) && nb_read != 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(buf);
			free(line);
			return (NULL);
		}
		buf[nb_read] = '\0';
		line = join_line(line, buf);
	}
	free(buf);
	return (line);
}

/*Three phases: read and save, prepare line and keep next line*/
char	*get_next_line(int fd)
{
	static char	*kept;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!kept || !end_line(kept))
	{
		kept = line_read(fd, kept);
		if (!kept)
			return (NULL);
	}
	line = line_returned(kept);
	if (!line)
	{
		free(kept);
		free(line);
		return (NULL);
	}
	kept = next_line(kept);
	return (line);
}
/*
int	main(void)
{
	int	fd;
	char	*lines;

	fd = open("trying_read.txt", O_RDONLY);
	lines = "";
	while (lines != NULL)
	{	
		lines = get_next_line(fd);
		//printf("--MAIN: lines <%s>\n", lines);
		if (lines)
			printf("**RESULT %s\n\n", lines);
		free(lines);
	}
	return (0);
}*/
