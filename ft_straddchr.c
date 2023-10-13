/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:02:34 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/13 15:09:19 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_straddchr(char *str, char c)
{
	char	*out;
	int		len;

	len = 0;
	if (str != NULL)
		len = ft_strlen(str);
	out = (char *)malloc(sizeof(char) * (len + 2));
	if (out == NULL)
		return (NULL);
	if (str != NULL)
		ft_strlcpy(out, (char *)str, len + 1);
	out[len] = c;
	out[len + 1] = '\0';
	if (str != NULL)
		free(str);
	return (out);
}
