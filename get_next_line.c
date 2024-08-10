/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/10 22:45:11 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	wrong(char *line, char *buf, static char * aux);
{
	free(line);
	free(buf);
	free(aux);
	return (NULL);
}

static char	*end_line(const char *s) /*As strchr, but just for '\n'*/
{
	while (*s)
	{
		if (*s == '\n')
			return ((unsigned char *)s);
		s++;
	}
	return (0);
}

static char	*line_returned(char *aux)/*It's like substr, 
					  to get the complete line*/
{
	char	*the_line;
	char	*end;
	size_t	len;

	if (aux)
	{
		end = end_line(aux);
		len = strlen_gnl(aux) - strlen_gnl(end);
		the_line = (char *)malloc((len + 1) * sizeof(char));
		the_line = memcpy_line(the_line, aux, len);
		if (!the_line)
			return (NULL);
		the_line[len] = '\0';
	}
	return (the_line);
}

char	*get_next_line(int fd)
{
	static char	*aux;
	char		*line;
	char		*buf;
	ssize_t		nb_read;

	if (aux)
	{
			line = dup_line(aux);
			free(aux);
	}
	while (nb_read != 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE); //May I protect
						       //the BUFFER_SIZE
						       //from SSIZE_MAX value
		if (nb_read <= 0)
			return (NULL);
		buf[nb_read] = '\0';
		aux = join_line(line, buf);
		if (!aux)
			return (NULL);
		if (end_line(buf)) /*This conditional must stop the function*/
		{
			line = line_returned(aux);
			if (!line)
			{
				free(line);
				free(buf);
				free(aux);
				return (NULL);
			}
			free(buf);
		}
		else
		{
			line = dup_line(aux);//End of file or not found \n
			free(aux);
			free(buf);
			if (!line)
			{
				free(line);
				return (NULL);
			}
		}
	}
	return	(line);// if nb_read == 0, return line that we have
}
/*
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
}*/
