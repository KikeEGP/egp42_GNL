/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/08 21:51:24 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*end_line(const char *s) /*As strchr, but just for '\n'*/
{
	while (*s)
	{
		if (*s == '\n')
			return ((unsigned char *)s+1);
					//If finds end of line, will
					//return pointer to new line
		s++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*line; 
	char		aux;
	static	char	*buf;
	ssize_t		nb_read;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (0);
		//Don't forget to asign '\0'
		//
	nb_read = -1;
	while (nb_read != 0) //Maybe this while must be until I don't find
			     //the \n, because I don't have to reach
			     //end of line. Maybe I need to be prepared
			     //for both cases, though
	{
		nb_read = read(fd, buf, BUFFER_SIZE); //May I protect
						       //the BUFFER_SIZE
						       //from SSIZE_MAX value
		if (nb_read < 0)
			return (NULL);
		aux = strjoin(line, buf);
		if (line)
			free(line);
		if (!end_line(buf))
			line = strdup(aux);
		if (end_line(buf))
		{
			end = end_line(buf);// REMOVE THIS LINE!!!
					    // THIS FUNCTION MUST RUN WITH
					    // FIRST CALL OR 25th CALL
					    // SO BUFFER MUST BE ALWAYS
					    // THE VAR WHICH LOCATES THE POINTER
					    // TO READ FIRST
			len = (strlen(line) - strlen(end));
			line = substr(line, 0, len);
			free(/*WATCH OUT, SOMETHINNG MUST BE FREE
			OR TAKE LESS MEMORY INSTEAD*/)
			if (!line)
			{
				free(line);
				return (NULL);
			}
		}
		
		//So... have we reached the \n? 
				  //You should check it
			//Now I only want to store in line from buf[0]
			//to buf[n] == end_line(buf). HOW?

	}
	return (line);
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
