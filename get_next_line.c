/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/04 20:58:07 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	end_line(const char *s) /*As strchr, but just for '\n'*/
{
	while (*s)
	{
		if (*s == '\n')
			return ((char *)s+1);//If finds end of line, will
					     //return pointer to new line
		s++;
	}
	return (0)
}

char	*get_next_line(int fd)
{
	char	*line; 
	char	aux;
	char	*buf;
	ssize_t	nb_read;

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
		buf[nb_read] = '\0'; //doing this, buffer is converted
				     //to string, which we can manage
				     //TARGET: save all buffers in a
				     //string that we will return as "line"
				     //when we reach '\n'
		//So... have we reached the \n? You should check it
		//Also, you have to save content 
		//from the buffer in a heap's var
		//
		//Before you save the buffer in heap, check it wth strchr
		//If there's no \n, copy complete. If you find \n,
		//copy just to \n, an keep next chars for next line
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
