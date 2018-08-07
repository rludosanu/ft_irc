/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:55:36 by rludosan          #+#    #+#             */
/*   Updated: 2018/01/03 11:30:08 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

char		*ft_strsub(char *src, int head, int tail);
int			ft_strequ(char *s1, char *s2);
size_t		ft_strlen(char *s);
char		*ft_strcpy(char *dest, char *src);
int			ft_strchr(char *s, int c);
char		*ft_strcat(char *dst, char *src);
char		*ft_strcatsp(char *dst, char *src);
char		*ft_strcatnl(char *dst, char *src);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);

#endif
