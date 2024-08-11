/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/11 22:25:48 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	failure(char *line, char *buf, char *aux)
{
	if (line)
		free(line);
	if (buf)
		free(buf);
	if (aux)
		free(aux);
}

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
	char	*aux;
	char	*end;
	end = end_line(buf);
	if (end+1 == NULL)
	{
		free(buf);
		return (NULL);
	}
	aux = dup_line(end+1);
	free(buf);
	return (aux);
}

/*				It's like substr to get the complete line*/
static char	*line_returned(char *aux)
{
	char	*the_line;
	char	*end;
	size_t	len;

	if (aux)
	{
		end = end_line(aux);
		len = strlen_gnl(aux) - strlen_gnl(end);
		the_line = (char *)malloc((len + 1) * sizeof(char));
		if (!the_line)
			return (NULL);
		the_line[len] = '\0';
		the_line = memcpy_line(the_line, aux, len);
		return (the_line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*aux;
	char		*line;
	char		*buf;
	ssize_t		nb_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (aux)//WHEN COMPILE, THIS MAKES ERROR 'CAUSE IT'S UNINITIALIZE
		//CHECK ALSO var line at the while, 89.9
	{
			line = dup_line(aux);
			free(aux);
	}
	nb_read = 1;
	while (line && nb_read != 0)//BE_CAREFUL, AT END OF FILE YOU MUST RETURN LINE
	{
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
		{
			failure(line, buf, aux);
			return (NULL);
		}
		nb_read = read(fd, buf, BUFFER_SIZE); //May I protect
						       //the BUFFER_SIZE
						       //from SSIZE_MAX value
		if (nb_read <= 0)
		{
			failure(line, buf, aux);
			return (NULL);
		}
		buf[nb_read] = '\0';
		aux = join_line(line, buf);
		if (!aux)
		{
			failure(line, buf, aux);
			return (NULL);
		}
		if (end_line(buf)) /*This conditional must stop the function*/
		{
			line = line_returned(aux);
			if (!line)
			{
				failure(line, buf, aux);
				return (NULL);
			}
			free(aux);
			aux = keep_line(buf);
			free(buf);
			return (line);
		}
		else
		{
			line = dup_line(aux);//End of file or not found \n
			if (!line)
			{
				failure(line, buf, aux);
				return (NULL);
			}
			free(aux);
			free(buf);

		}
	}
	if (line)
		return (line);// if nb_read == 0, return line that we have
	return	(0);
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
