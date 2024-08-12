/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:30:21 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/12 20:45:05 by enrgil-p         ###   ########.fr       */
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
	if (end+1 == NULL)
	{
		free(buf);
		return (NULL);
	}
	next = dup_line(end+1);
	free(buf);
	return (next);
}

/*				It's like substr to get the complete line*/
static char	*line_returned(char *aux)
{
	char	*the_line;
	char	*end;
	size_t	len;

	if (aux != NULL)
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
/*	THIS IS A TRY TO DIVIDE THE FUNCTION	*/
static char	*line_readed(int fd, char *aux, char *line)
{
	ssize_t	nb_read;
	char	*buf;

	nb_read = 1;
	while (!end_line(buf) || nb_read != 0)
	{
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[nb_read] = '\0';
		aux = join_line(line, buf);
	}
	return (aux);
}
/*		ESTO ESTÁ EN CUARENTENA		*/

char	*get_next_line(int fd)
{
	static char	*next;/*Just for next line*/
	char		*line;/*char * that i return*/
	char		*buf;/*For read*/
	ssize_t		nb_read;/*For read*/

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (next != NULL)//CHECK var line, UNINITIALIZE
	{
			line = dup_line(next);
			free(next);
	}
	nb_read = 1;//ZONA DE LECTURA
	while (nb_read != 0)//BE_CAREFUL, AT END OF FILE YOU MUST RETURN LINE
	{
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (NULL);
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[nb_read] = '\0';
		line = join_line(line, buf);//AQUÍ SE JUNTA LO QUE VA LEYENDO
		if (!line)
		{
			/*HEY, DO SOMETHING HERE*/
		}
		if (end_line(buf)) /*This conditional must stop the function*/
		{
			line = line_returned(line);//AQUÍ INVOCAMOS FUNCIÓN
						  //PARA DEVOLVER LÍNEA Y PARAR
			if (!line)
			{
				failure(line, buf, aux);
				return (NULL);
			}
			next = keep_line(buf);//AQUÍ INVOCAMOS FUNCIÓN PARA
					     //GUARDAR INICIO DE PRÓXIMA
			free(buf);
			return (line);//STOP
		}
	}
	if (line)
		return (line);// if nb_read == 0, return line that we have
	return	(0);
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
