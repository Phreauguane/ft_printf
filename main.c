/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:13:32 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/14 18:55:58 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "limits.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h> /* exit */
#include <stdio.h> /* printf */

char *flags = "-0# +";

int urandom_fd = -2;

void urandom_init() 
{
  urandom_fd = open("/dev/urandom", O_RDONLY);

  if (urandom_fd == -1) {
    int errsv = urandom_fd;
    printf("Error opening [/dev/urandom]: %i\n", errsv);
    exit(1);
  }
}

unsigned long urandom() 
{
  unsigned long buf_impl;
  unsigned long *buf = &buf_impl;

  if (urandom_fd == -2) {
    urandom_init();
  }

  /* Read sizeof(long) bytes (usually 8) into *buf, which points to buf_impl */
  read(urandom_fd, buf, sizeof(long));
  return buf_impl;
}

char	*gen_random_str(int size)
{
	urandom_init();
	int		len = urandom() % 255;
	if (size > 0)
		len = size;
	char	*str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (--len >= 0)
		str[len] = urandom() % 255;
	return (str);
}

void	gen_random_format(char **str, char spec)
{
	*str = ft_straddchr(*str, '|');
	*str = ft_straddchr(*str, '%');
	urandom_init();
	for (int i = 0; i < 6; i++)
	{
		*str = ft_straddchr(*str, flags[urandom() % 5]);
	}
	char *itoaout = ft_itoa_base(urandom() % 50, "0123456789", 0);
	*str = ft_strcat_malloc(*str, itoaout);
	free(itoaout);
	*str = ft_straddchr(*str, '.');
		  itoaout = ft_itoa_base(urandom() % 50, "0123456789", 0);
	*str = ft_strcat_malloc(*str, itoaout);
	free(itoaout);
	*str = ft_straddchr(*str, spec);
}

int	main(int ac, char **av)
{
	int chr_test = 0;
	int str_test = 0;
	int ptr_test = 0;
	int	bonus_test = 1;
	if (str_test) printf("|	STR TESTS	|\n");
	for (int i = 0; i < 5 && str_test; i++)
	{
		printf("Test %d\n", i + 1);
		char	*str = gen_random_str(0);
		int res1 = ft_printf("%s", str);
		printf("|\n----\n");
		int res2 = printf("%s", str);
		printf("|\n");
		printf("Your return value : %d\n Original return value : %d\n", res1, res2);
		printf("\n=====================\n");
		free(str);
	}
	if (chr_test) printf("|	CHAR TESTS	|\n");
	for (int i = 0; i < 4 && chr_test; i++)
	{
		printf("Test %d\n", i + 1);
		urandom_init();
		char	*s = gen_random_str(8);
		int res1 = ft_printf("%c%c%c%c%c%c%c%c", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);
		printf("|\n----\n");
		int res2 = printf("%c%c%c%c%c%c%c%c", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);
		printf("|\n");
		printf("Your return value : %d\n Original return value : %d\n", res1, res2);
		printf("\n=====================\n");
		free(s);
	}
	if (ptr_test) printf("|	POINTER TESTS	|\n");
	for (int i = 0; i < 1 && ptr_test; i++)
	{
		printf("Test %d\n", i + 1);
		urandom_init();
		void	*s = gen_random_str(64);
		int res1 = ft_printf("%p", s);
		printf("|\n----\n");
		int res2 = printf("%p", s);
		printf("|\n");
		printf("Your return value : %d\n Original return value : %d\n", res1, res2);
		printf("\n=====================\n");
		free(s);
	}
	if (bonus_test) printf("|  BONUS TESTS 	|\n");
	for (int i = 0; i < 5 && bonus_test; i++)
	{
		char *format = NULL;
		gen_random_format(&format, 'c');
		gen_random_format(&format, 's');
		gen_random_format(&format, 'p');
		gen_random_format(&format, 'd');
		gen_random_format(&format, 'i');
		gen_random_format(&format, 'u');
		gen_random_format(&format, 'x');
		gen_random_format(&format, 'X');
		gen_random_format(&format, '%');
		printf("Test using format : %s\n", format);
		urandom_init();
		int	randomint = urandom() % 4096;
		unsigned long long pointer = urandom() % LLONG_MAX;
		int res1 = ft_printf(format, '4', "test ft_printf 42", pointer, randomint, -randomint, randomint - 255, randomint - 2048, randomint - 4096);
		printf("|\n----\n");
		int res2 = printf(format, '4', "test ft_printf 42", pointer, randomint, -randomint, randomint - 255, randomint - 2048, randomint - 4096);
		printf("|\n");
		printf("Your return value : %d\n Original return value : %d\n", res1, res2);
		printf("\n=====================\n");
	}
}
