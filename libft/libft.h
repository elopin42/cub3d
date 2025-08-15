/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-cout <lle-cout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:57:57 by lle-cout          #+#    #+#             */
/*   Updated: 2025/08/15 13:04:27 by lle-cout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// LIBFT
size_t		ft_arraylen(void **array);
int			ft_atoi(char *nptr);
long long	ft_atoll(char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_fstrjoin(char *s1, char *s2, short fs1, short fs2);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
char		*ft_itoa(int n);
void		*ft_memchr(void *s, int c, size_t n);
int			ft_memcmp(void *s1, void *s2, size_t n);
void		*ft_memcpy(void *dest, void *src, size_t n);
void		*ft_memmove(void *dest, void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_print_strarray(char **ptr);
int			ft_putbase_fd(
				unsigned long long nbr, char *base, char *prefix, int fd);
int			ft_putchar_fd(char c, int fd);
int			ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);
int			ft_putstr_fd(char *s, int fd);
char		**ft_split(char *s, char c);
char		*ft_strchr(char *s, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_3(char *s1, char *s2, char *s3);
size_t		ft_strlcat(char *dst, char *src, size_t dsize);
size_t		ft_strlcpy(char *dst, char *src, size_t dsize);
int			ft_strlen(char *s);
char		*ft_strmapi(char *s, char (*f)(unsigned int, char));
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strnstr(char *s1, char *s2, size_t n);
char		*ft_strrchr(char *s, int c);
int			ft_strstr(char *b, char *li);
char		*ft_strtrim(char *s1, char *set);
char		*ft_substr(char **s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);

// FT_PRINTF
int			ft_printf(int fd, char *format, ...);

// GNL
# define BUFFER_SIZE 50

typedef struct s_struct
{
	char		read_buffer[BUFFER_SIZE];
	ssize_t		b_read;
	ssize_t		next_index;
}	t_gnl;

char		*get_next_line(int fd);

#endif
