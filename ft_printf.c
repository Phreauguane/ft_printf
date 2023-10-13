/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:21:42 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/13 15:07:01 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
