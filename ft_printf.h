/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 02:42:03 by ulee              #+#    #+#             */
/*   Updated: 2021/02/10 04:09:56 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "./libft/libft.h"

# define TYPE "diucsxXp%"

typedef struct s_flags{
	int			len;
	int			minus;
	int			zero;
	int			width_minus;
	int			width;
	int			dot;
	int			dot_width;
	int			star;
	int			dot_star;
	int			print_zero;
	int			print_space;
	long long	arg;
	char		*string;
}				t_flags;

int				ft_printf(const char *s, ...);
int				ft_istype(int c);
void			delete_multiflag(t_flags *flags);
void			check_flag(char **percent, char c, t_flags *flags, int isdot);
void			check_width(char **percent, t_flags *flags, int isdot);
void			check_format(char **percent, t_flags *flags);
int				check_len(long long n, t_flags *flags);
int				check_hexlen(long long n, t_flags *flags);
int				check_strlen(t_flags *flags);
void			set_width(t_flags *flags, int len);
void			set_star(va_list ap, t_flags *flags);
void			set_arg(char *percent, t_flags *flags, va_list ap);
int				set_len(char *percent, t_flags *flags);
void			set_format(char *percent, t_flags *flags, va_list ap);

int				print_string(const char *s, int len);
int				print_spaces(t_flags *flags);
int				print_zeros(t_flags *flags);
int				print_minus(t_flags *flags, int position);
int				print_arg(char *percent, t_flags *flags);
int				print_format(char *percent, t_flags *flags);

int				print_num(t_flags *flags, size_t arg, char tyoe);
int				print_numhex(t_flags *flags, size_t arg, char type, char *base);
int				print_int(t_flags *flags, char type);
int				print_char(t_flags *flags);
int				print_chars(t_flags *flags);
int				print_hex(t_flags *flags, char type);

#endif
