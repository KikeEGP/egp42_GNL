/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/08 19:47:37 by enrgil-p         ###   ########.fr       */
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
	char	*line; 
	char	aux;
	char	*buf;
	ssize_t	nb_read;


	buf = (char *)malloc((nb_read + 1) * sizeof(char));
		//Don't forget to asign '\0'
		//
	while (nb_read != 0) //Maybe this while must be until I don't find
			     //the \n, because I don't have to reach
			     //end of line. Maybe I need to be prepared
			     //for both cases, though
	{
		nb_read = read (fd, buf, BUFFER_SIZE); //May I protect
						       //the BUFFER_SIZE
						       //from SSIZE_MAX value
		if (nb_read < 0)
			return (NULL);
		//I must allocate memory now
		//TARGET: save all buffers in a string that we will 
		//return as "line" when we reach '\n'
		//
		//So... have we reached the \n? You should check it
		//
		//Before you save the buffer in heap, check it wth strchr
		//If there's no \n, copy complete. If you find \n,
		//what can you do? Save all and then only return until \n?
		//Save until \n, and take \n+1 for next line?
		if (!end_line(buf)) //Maybe I need do this in case of \n too
		{
			aux = strjoin(line, buf);
			if (line)
				free(line);
			line = strdup(aux);
		}
		if (end_line(buf))
		{
			
			//Now I only want to store in line from buf[0]
			//to buf[n] == end_line(buf). HOW?
		}

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
