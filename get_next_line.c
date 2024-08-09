/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/09 20:50:05 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	*line;
	char	aux;
	char	*buf;
	ssize_t	nb_read;

	while (/*????????????*/)/*LOOP MUST STOP AFTER end_line(buf)!!*/
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
		free(line);
		if (end_line(buf))
		{
			line = line_returned(aux);
			free(/*WATCH OUT, SOMETHINNG MUST BE FREE
			OR TAKE LESS MEMORY INSTEAD*/)
		}
		else
			line = dup_line(aux);//End of file or not found \n
		//else
		{
			/*A FUNCTION TO CHECK IF MUST RETURN NULL AND/OR FREE*/
			//free(line);
			//return (NULL);
		}
	}
	return	(line);}
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
