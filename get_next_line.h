/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrgil-p <enrgil-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:06:49 by enrgil-p          #+#    #+#             */
/*   Updated: 2024/08/30 16:32:32 by enrgil-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h> /*read()*/
# include <fcntl.h> /*open()*/
# include <stdlib.h> /*malloc and free*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 19
# endif

char	*get_next_line(int fd);
/*	Part 2: functions at get_next_line_utils.c	*/
size_t	strlen_gnl(const char *str);/*			normal	strlen	*/
char	*end_line(const char *s); /*like strchr but only for \n*/
void	*memcpy_line(void *dest, const void *src, size_t len);/*memcpy	*/
char	*dup_line(const char *aux);/*				strdup	*/
char	*join_line(char *line, char *buffer);/*			strjoin	*/

#endif
