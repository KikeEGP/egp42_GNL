/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/20 20:52:20 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*					As strchr, but just for '\n'*/
static char	*end_line(const char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return ((char *)s);
		s++;
	}
	return (0);
}

/*			If buffer has chars after \n, keep for next call*/
static char	*keep_line(char *buf)
{
	char	*next;
	char	*end;

	end = end_line(buf);
	if (end)
	{
		next = dup_line(end + 1);
		if (!next)
			return (NULL);
		return (next);
	}
	return (NULL);
}

/*				It's like substr to get the complete line*/
static char	*line_returned(char *line)
{
	char	*the_line;
	char	*end;
	size_t	len;

	if (line != NULL && end_line(line))
	{
		end = end_line(line);
		len = strlen_gnl(line) - strlen_gnl(end);
		the_line = (char *)malloc((len + 1) * sizeof(char));
		if (!the_line)
			return (NULL);
		the_line[len] = '\0';
		the_line = memcpy_line(the_line, line, len);
		return (the_line);
	}
	return (NULL);
}

/*				Scope to read and save line unitl \n	*/
static char	*line_readed(int fd, char *line)
{
	ssize_t	nb_read;
	char	*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
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

char	*get_next_line(int fd)
{
	static char	*next;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (next && end_line(next))
		line = dup_line(next);
	else
	{
		line = line_readed(fd, next);
		if (!line)
			return (NULL);
	}
	free(next);
	next = keep_line(line);
	line = line_returned(line);
	if (!line)
	{
		free(next);
		free(line);
		return (NULL);
	}
	return (line);
}

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
}
