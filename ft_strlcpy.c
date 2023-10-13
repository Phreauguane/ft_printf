/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:24:48 by nbiron            #+#    #+#             */
/*   Updated: 2023/10/13 15:09:09 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	i2;

	i = 0;
	i2 = 0;
	while (src[i] != '\0')
		i++;
	if (size > 0)
	{
		while (src[i2] != '\0' && i2 < size - 1)
		{
			dest[i2] = src[i2];
			i2++;
		}
		dest[i2] = '\0';
	}
	return (i);
}
