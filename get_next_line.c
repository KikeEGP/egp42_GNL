/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/14 14:55:13 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*					As strchr, but just for '\n'*/
static char	*end_line(const char *s)
{
	printf("--This is end_line(). We have received <%s>\n", s);
	while (*s)
	{
		if (*s == '\n')
		{
			printf("--This is end_line(). ptr now is <%s>\n", s);
			return ((char *)s);
		}
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
	if (end + 1 != NULL)
	{
		next = dup_line(end + 1);
		free(buf);
		return (next);
	}
	free(buf);
	return (NULL);
}

/*				It's like substr to get the complete line*/
static char	*line_returned(char *line)
{
	char	*the_line;
	char	*end;
	size_t	len;

	if (line != NULL)
	{
		printf("--Returned have <%s>.\n", line);/*BUG*/
		end = end_line(line);
		printf("--At returned(). End ptr to <%s>\n", end);/*BUG*/
		len = strlen_gnl(line) - strlen_gnl(end);
		the_line = (char *)malloc((len + 1) * sizeof(char));
		if (!the_line)
			return (NULL);
		the_line[len] = '\0';
		printf("--Returned created the_line <%s>.\n", the_line);/*BUG*/
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
		printf("--read() readed <%s>\n", buf);/*DEBUG, REMOVE LATER	*/
		line = join_line(line, buf);
		printf("--join_line returns <%s>\n", line);/*DEBUG, REMOVE LATER*/
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
	line = line_readed(fd, next);
	if (!line)
		return(NULL);
	free (next);
	/*HEY, THIS BELOW IS TO DEBUG. REMOVE LATER*/
	printf("--GNL here. <%s> ready to enter to keep_line()\n", line);
	next = keep_line(line);
	/*HEY, THIS BELOW IS TO DEBUG. REMOVE LATER*/
	printf("--GNL here. <%s> ready to enter to returned()\n", line);
	line = line_returned(line);
	if (!line)
	{
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
	while (get_next_line(fd) != NULL)
	{	
		lines = get_next_line(fd);
		if (lines)
			printf("%s", lines);
		free(lines);
	}
	return (0);
}
