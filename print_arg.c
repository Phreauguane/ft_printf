/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:26:02 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/13 16:06:32 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(t_flags flags, char **str, char c)
{
	if (flags.length <= 1)
		*str = ft_straddchr(*str, c);
	else
	{
		if ((flags.flags & 0b100000) != 0)
			*str = ft_straddchr(*str, c);
		while (flags.length > 1)
		{
			*str = ft_straddchr(*str, ' ');
			flags.length--;
		}
		if ((flags.flags & 0b100000) == 0)
			*str = ft_straddchr(*str, c);
	}
}

void	print_str(t_flags flags, char **str, const char *s)
{
	int		len;
	char	*print;

	if (s == NULL)
		print = ft_strcat_malloc(NULL, "(null)");
	else
		print = ft_strcat_malloc(NULL, (char *)s);
	if (flags.precision >= 0 && flags.precision < ft_strlen(print))
		print[flags.precision] = '\0';
	len = ft_strlen(print);
	if ((flags.flags & 0b100000) != 0)
		*str = ft_strcat_malloc(*str, print);
	while (flags.length - len > 0)
	{
		*str = ft_straddchr(*str, ' ');
		flags.length--;
	}
	if ((flags.flags & 0b100000) == 0)
		*str = ft_strcat_malloc(*str, print);
	free(print);
}

void	print_hex(t_flags flags, char **str, unsigned long long int i)
{
	char	*num;
	char	*temp;
	int		k;

	k = -1;
	if (flags.spec == 'p' && i == 0)
	{
		print_str(flags, str, "(nil)");
		return ;
	}
	num = ft_strcat_malloc(NULL, "");
	if (flags.spec == 'p' || ((flags.flags & 0b001000) != 0))
		num = ft_strcat_malloc(num, "0x");
	temp = ft_itoa_base(i, "0123456789abcdef", flags.spec == 'p');
	while (flags.length > (ft_strlen(num) + ft_strlen(temp))
		&& !(flags.flags & 0b100000) && (flags.flags & 0b010000))
		num = ft_straddchr(num, '0');
	num = ft_strcat_malloc(num, temp);
	free(temp);
	while (num[++k] && flags.spec == 'X')
		num[k] = ft_toupper(num[k]);
	flags.precision = -1;
	print_str(flags, str, num);
	free(num);
}

static char	*fill_string(char *itoa_out, t_flags flags, long int i)
{
	char	*out;
	int		numz;

	numz = 0;
	if (flags.precision >= 0)
		numz = flags.precision - ft_strlen(itoa_out);
	else if (!(flags.flags & 0b100000) && (flags.flags & 0b010000))
		numz = flags.length - ft_strlen(itoa_out);
	out = NULL;
	if (i < 0)
		out = ft_straddchr(out, '-');
	if (i >= 0 && (flags.flags & 0b000010))
		out = ft_straddchr(out, '+');
	else if (i >= 0 && (flags.flags & 0b000100))
		out = ft_straddchr(out, ' ');
	while (numz-- > 0)
		out = ft_straddchr(out, '0');
	out = ft_strcat_malloc(out, itoa_out);
	return (out);
}

void	print_int(t_flags flags, char **str, long int i)
{
	char	*num;
	char	*temp;

	temp = ft_itoa_base(i, "0123456789", 0);
	num = fill_string(temp, flags, i);
	flags.precision = -1;
	print_str(flags, str, num);
	free(temp);
	free(num);
}
