/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:06:49 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/18 19:07:38 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h> // read()
# include <fcntl.h> // open()
# include <stdlib.h> // malloc and free
#include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE
# endif

char	*get_next_line(int fd);/*
			
			functions at get_next_line_utils.c
				  					*/
size_t	strlen_gnl(const char *str);/*			normal	strlen	*/
void	*memcpy_line(void *dest, const void *src, size_t len);/*memcpy	*/
char	*dup_line(const char *aux);/*				strdup	*/
char	*join_line(char const *line, char const *buffer);/*	strjoin	*/

#endif
