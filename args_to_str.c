/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:53:40 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/13 15:57:05 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parse_flags(char *str, t_flags *flags)
{
	int	i;

	i = 1;
	while (str[i] && !ft_strchr(SPECS, str[i]) && str[i] != '.'
		&& (!ft_isdigit(str[i]) || str[i] == '0'))
	{
		if (str[i] == '-')
			flags->flags |= 0b100000;
		else if (str[i] == '0')
			flags->flags |= 0b010000;
		else if (str[i] == '#')
			flags->flags |= 0b001000;
		else if (str[i] == ' ')
			flags->flags |= 0b000100;
		else if (str[i] == '+')
			flags->flags |= 0b000010;
		else
		{
			flags->flags |= 0b000001;
			return (i);
		}
		i++;
	}
	return (i);
}

static void	parse_length(char **str, va_list params, t_flags *flags)
{
	if (ft_isdigit(**str) || **str == '*')
	{
		if (**str == '*')
			flags->length = (int)va_arg(params, int);
		else
			flags->length = ft_atoi(*str);
		while (ft_isdigit(**str) || **str == '*')
			(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		if (**str == '*')
			flags->precision = (int)va_arg(params, int);
		else
			flags->precision = ft_atoi(*str);
		while (ft_isdigit(**str) || **str == '*')
			(*str)++;
	}
}

static void	parse_arg(char **str, va_list params, t_flags *flags)
{
	flags->flags = 0;
	flags->length = 0;
	flags->precision = -1;
	flags->spec = '\0';
	*str += parse_flags(*str, flags);
	parse_length(str, params, flags);
	if (ft_strchr(SPECS, **str) && **str != '\0')
	{
		flags->spec = **str;
		(*str)++;
	}
	else
		flags->flags |= 0b000001;
}

static void	add_arg(t_flags flags, va_list params, char **str)
{
	int	spec;

	spec = (int)(ft_strchr(SPECS, flags.spec) - SPECS);
	if (spec == SP_CHR)
		print_char(flags, str, (char)va_arg(params, int));
	else if (spec == SP_STR)
		print_str(flags, str, (const char *)va_arg(params, const char *));
	else if (spec == SP_PTR)
		print_hex(flags, str, (unsigned long long int)va_arg(params, void *));
	else if (spec == SP_DEC || spec == SP_INT)
		print_int(flags, str, (long int)va_arg(params, int));
	else if (spec == SP_UIN)
		print_int(flags, str, (unsigned int)va_arg(params, int));
	else if (spec == SP_HEX || spec == SP_CAP_HEX)
		print_hex(flags, str, (unsigned int)va_arg(params, int));
}

void	args_to_str(char **fmt, va_list params, char **str)
{
	char	*arg;
	char	*temp;
	t_flags	flags;

	temp = *fmt;
	parse_arg(fmt, params, &flags);
	if (flags.flags % 2)
	{
		(*fmt)++;
		arg = ft_substr(temp, 0, (*fmt - temp));
		*str = ft_strcat_malloc(*str, arg);
	}
	else
	{
		if (flags.spec == '%')
			*str = ft_straddchr(*str, '%');
		else
			add_arg(flags, params, str);
	}
}
