/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:21:42 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/14 19:26:32 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_pre(t_flags flags, char **str)
{
	if (flags.spec == 'p' || (flags.flags & 0b001000))
	{
		if (flags.flags & 0b000010 && flags.spec == 'p')
			*str = ft_straddchr(*str, '+');
		else if (flags.flags & 0b000100 && flags.spec == 'p')
			*str = ft_straddchr(*str, ' ');
		*str = ft_strcat_malloc(*str, "0x");
	}
}

void	add_zer(t_flags flags, char **str, char *itoa_out)
{
	int		numz;

	numz = 0;
	if (flags.precision >= 0)
		numz = flags.precision - ft_strlen(itoa_out);
	else if (!(flags.flags & 0b100000) && (flags.flags & 0b010000))
		numz = flags.length - ft_strlen(itoa_out);
	while (numz-- > 0)
		*str = ft_straddchr(*str, '0');
	*str = ft_strcat_malloc(*str, itoa_out);
}

int	ft_printf(const char *fmt, ...)
{
	t_flags	flags;
	char	*str;
	char	*format;
	va_list	params;

	str = NULL;
	format = (char *)fmt;
	va_start(params, fmt);
	while (*format)
	{
		if (*format == '%')
			args_to_str(&format, params, &str);
		else
		{
			str = ft_straddchr(str, *format);
			format++;
		}
	}
	va_end(params);
	ft_putstr_fd(str, 1);
	flags.length = ft_strlen(str);
	free(str);
	return (flags.length);
}
