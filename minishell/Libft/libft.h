/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:51:51 by kakra             #+#    #+#             */
/*   Updated: 2024/11/21 21:59:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

void			ft_remove_chars(char *str, const char *remove);
int				is_single_quote(char c);
char			**clean_args(char **argv);
char			*safe_strjoin(char *s1, char *s2);
int				is_double_quote(char c);
char			*ft_strndup(const char *s, size_t n);
bool			ft_isspace(char input);
int				ft_strcmp(char *s1, char *s2);
void			freearray(char **str);
int				ft_doublelength(char **str);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, int n);
long			ft_strtol(const char *str, int *error);
void			*ft_calloc(size_t nelem, size_t size);
int				ft_isalnum(int arg);
int				ft_isalpha(int i);
int				ft_isascii(int c);
int				ft_isdigit(int i);
int				ft_isprint(int c);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *str1, const void *str2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strchr(char *str, int c);
char			*ft_strdup(char *str);
unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size);
unsigned int	ft_strlcpy(char *dest, const char *src, size_t size);
int				ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(char *str, int c);
int				ft_tolower(int str);
int				ft_toupper(int str);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
int				twodsize(char **str);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_lstsize(t_list *lst);
char			**add_string_to_array(char **array, int size,
					const char *new_string);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strncpy(char *dest, char *src, int n);
long			ft_atol(const char *str);

#endif