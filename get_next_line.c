/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/03 20:05:39 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_nextline.h"

char	*get_next_line(int fd)
{
	char	*line; //May you need to allocate mem here?
		       //How many? Maybe, BUFFER_SIZE plus BUF_SIZE...
		       //until you don't reach \n?
	char	*buf;
	ssize_t	nb_read;
	
	while (nb_read != 0)
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
	}
	return (line);
}
/*
int	main(void)
{
	int	fd;
	char	*lines;

	fd = open("trying_read.txt", O_RDONLY);
	return (0);
}*/
