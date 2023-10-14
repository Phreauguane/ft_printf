/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:09:26 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/14 19:26:28 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define SPECS "cspdiuxX%*"
# define FLAGS "-0#. +"
# define SP_CHR 0
# define SP_STR 1
# define SP_PTR 2
# define SP_DEC 3
# define SP_INT 4
# define SP_UIN 5
# define SP_HEX 6
# define SP_CAP_HEX 7

typedef struct flags_s
{
	char	flags;
	char	spec;
	int		length;
	int		precision;
}	t_flags;

void			args_to_str(char **fmt, va_list params, char **str);
void			print_char(t_flags flags, char **str, char c);
void			print_str(t_flags flags, char **str, const char *s);
void			print_hex(t_flags flags, char **str, unsigned long long i);
void			print_int(t_flags flags, char **str, long int i);
int				ft_printf(const char *fmt, ...);
int				ft_atoi(const char *nptr);
char			*ft_strchr(const char *s, int c);
int				ft_isdigit(int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strcat_malloc(char *dest, char *src);
char			*ft_straddchr(char *str, char c);
int				ft_strlen(const char *str);
void			ft_putstr_fd(char *s, int fd);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_itoa_base(long long int n, char *base, int ptr);
int				ft_toupper(int c);
void			add_pre(t_flags flags, char **str);
void			add_zer(t_flags flags, char **str, char *itoa_out);

#endif