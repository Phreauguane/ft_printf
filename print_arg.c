/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:26:02 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/15 17:58:31 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(t_flags flags, char **str, char c, int *l)
{
	(*l)++;
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
			(*l)++;
		}
		if ((flags.flags & 0b100000) == 0)
			*str = ft_straddchr(*str, c);
	}
}

void	print_str(t_flags flags, char **str, const char *s, int *l)
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
	(*l) += len;
	if ((flags.flags & 0b100000) != 0)
		*str = ft_strcat_malloc(*str, print);
	while (flags.length - len > 0)
	{
		*str = ft_straddchr(*str, ' ');
		flags.length--;
		(*l)++;
	}
	if ((flags.flags & 0b100000) == 0)
		*str = ft_strcat_malloc(*str, print);
	free(print);
}

void	print_hex(t_flags flags, char **str, unsigned long long i, int *l)
{
	char	*num;
	char	*temp;
	int		k;

	k = -1;
	if (flags.spec == 'p' && i == 0)
	{
		print_str(flags, str, "(nil)", l);
		return ;
	}
	num = ft_strcat_malloc(NULL, "");
	add_pre(flags, &num, i);
	temp = ft_itoa_base(i, "0123456789abcdef", flags.spec == 'p');
	add_zer(flags, &num, temp);
	free(temp);
	while (num[++k] && flags.spec == 'X')
		num[k] = ft_toupper(num[k]);
	flags.precision = -1;
	print_str(flags, str, num, l);
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
	if (i >= 0 && (flags.flags & 0b000010) && flags.spec != 'u')
		out = ft_straddchr(out, '+');
	else if (i >= 0 && (flags.flags & 0b000100) && flags.spec != 'u')
		out = ft_straddchr(out, ' ');
	while (numz-- > 0)
		out = ft_straddchr(out, '0');
	out = ft_strcat_malloc(out, itoa_out);
	return (out);
}

void	print_int(t_flags flags, char **str, long int i, int *l)
{
	char	*num;
	char	*temp;

	temp = ft_itoa_base(i, "0123456789", 0);
	if (i != 0 || flags.precision != 0)
		num = fill_string(temp, flags, i);
	else
		num = ft_straddchr(NULL, '\0');
	flags.precision = -1;
	print_str(flags, str, num, l);
	free(temp);
	free(num);
}
