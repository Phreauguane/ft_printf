/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:12:22 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/15 18:09:04 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	itoa_base_proc(char **str, long long int nb, char *base)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (nb < 0)
		nb *= -1;
	if (nb >= base_len)
		itoa_base_proc(str, nb / base_len, base);
	*str = ft_straddchr(*str, base[nb % base_len]);
}

static void	itoa_base_proc_ptr(char **s, unsigned long long int n, char *b)
{
	unsigned int	base_len;

	base_len = (unsigned int)ft_strlen(b);
	if (n >= base_len)
		itoa_base_proc_ptr(s, n / base_len, b);
	*s = ft_straddchr(*s, b[n % base_len]);
}

char	*ft_itoa_base(long long int n, char *base, int ptr)
{
	char	*str;

	str = NULL;
	if (ptr)
		itoa_base_proc_ptr(&str, (unsigned long long int)n, base);
	else
		itoa_base_proc(&str, n, base);
	return (str);
}
