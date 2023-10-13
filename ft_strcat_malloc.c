/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:40:25 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/13 15:09:16 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcat_malloc(char *dest, char *src)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	if (dest)
		len1 = ft_strlen(dest);
	len2 = ft_strlen(src);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	*str = '\0';
	if (dest)
	{
		ft_strlcpy(str, dest, len1 + 1);
		free(dest);
	}
	ft_strlcat(str, src, len1 + len2 + 1);
	return (str);
}
