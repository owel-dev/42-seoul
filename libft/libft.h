/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:54:17 by ulee              #+#    #+#             */
/*   Updated: 2021/08/26 15:11:43 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 32
# endif

# ifndef TYPE
#  define TYPE "diucsxXp%"
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_flags
{
	int				len;
	int				minus;
	int				zero;
	int				width_minus;
	int				width;
	int				dot;
	int				dot_width;
	int				star;
	int				dot_star;
	int				print_zero;
	int				print_space;
	long long		arg;
	char			*string;
}					t_flags;

void				*ft_memset(void *str, int c, size_t n);
void				*ft_bzero(void *array, size_t byte_size);
void				*ft_memcpy(void *copy, const void *origin, \
	size_t byte_size);
void				*ft_memccpy(void *copy, const void *origin, int target, \
	size_t byte_size);
void				*ft_memmove(void *copy, const void *origin, \
	size_t byte_size);
void				*ft_memchr(const void *array, int target, size_t byte_size);
int					ft_memcmp(const void *first, const void *second, \
	size_t byte_size);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *copy, const char *origin, \
	size_t char_count);
size_t				ft_strlcat(char *first, const char *second, \
	size_t total_len);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strnstr(const char *str, const char *part, size_t len);
int					ft_strncmp(const char *first, const char *second, \
	size_t len);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
void				*ft_calloc(size_t n, size_t size);
char				*ft_strdup(const char *s);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_itoa(int num);
char				*ft_substr(char const *str, unsigned int start_index, \
	size_t cut_size);
char				*ft_strjoin(char const *first, char const *second);
char				*ft_strtrim(char const *str, char const *remove_char);
char				**ft_split(char const *str, char c);
char				*ft_strmapi(char const *str, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void*));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
	void (*del)(void *));

int					get_next_line(int fd, char **line);

int					ft_printf(const char *s, ...);
int					ft_istype(int c);
void				delete_multiflag(t_flags *flags);
void				check_flag(char **percent, char c, t_flags *flags, \
	int isdot);
void				check_width(char **percent, t_flags *flags, int isdot);
void				check_format(char **percent, t_flags *flags);
int					check_len(long long n, t_flags *flags);
int					check_hexlen(long long n, t_flags *flags);
int					check_strlen(t_flags *flags);
void				set_width(t_flags *flags, int len);
void				set_star(va_list ap, t_flags *flags);
void				set_arg(char *percent, t_flags *flags, va_list ap);
int					set_len(char *percent, t_flags *flags);
void				set_format(char *percent, t_flags *flags, va_list ap);

int					print_string(const char *s, int len);
int					print_spaces(t_flags *flags);
int					print_zeros(t_flags *flags);
int					print_minus(t_flags *flags, int position);
int					print_arg(char *percent, t_flags *flags);
int					print_format(char *percent, t_flags *flags);

int					print_num(t_flags *flags, size_t arg, char tyoe);
int					print_numhex(t_flags *flags, size_t arg, char type, \
char *base);
int					print_int(t_flags *flags, char type);
int					print_char(t_flags *flags);
int					print_chars(t_flags *flags);
int					print_hex(t_flags *flags, char type);

int					ft_strcmp(char *one, char *two);

#endif
