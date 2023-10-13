/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:11:27 by nbiron            #+#    #+#             */
/*   Updated: 2023/10/13 15:10:03 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	char	*t;

	t = (char *)s;
	while (*t != (unsigned char)c && *t)
		t++;
	if (*t || (unsigned char)c == '\0')
		return (t);
	return (NULL);
}
