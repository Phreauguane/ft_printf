/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:13:32 by jde-meo           #+#    #+#             */
/*   Updated: 2023/10/15 15:12:19 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "limits.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *flags = "-0# +";
#define DEF "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_PURPLE "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_WHITE "\033[1;37m"
#define setColor(x) printf(x)

int urandom_fd = -2;

void	urandom_init() 
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
	for (int i = 0; i < 6; i++)
	{
		*str = ft_straddchr(*str, flags[urandom() % 5]);
	}
	char *itoaout = ft_itoa_base(urandom() % 30, "0123456789", 0);
	*str = ft_strcat_malloc(*str, itoaout);
	free(itoaout);
	*str = ft_straddchr(*str, '.');
		  itoaout = ft_itoa_base(urandom() % 30, "0123456789", 0);
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
	urandom_init();
	/*
					CHAR
	*/
	setColor(BOLD_CYAN);
	//if (chr_test)
	//{
	//	
	//}



	/*
					BONUS
	*/
	setColor(BOLD_CYAN);
	if (bonus_test) printf("|  BONUS TESTS 	|\n");
	for (int i = 0; i < 255 && bonus_test; i++)
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
		format = ft_straddchr(format, '|');
		int	randomint = urandom() % 4096;
		unsigned long long pointer = urandom() % LLONG_MAX;

		// store output in printf_out
		int	stdout_bk = dup(fileno(stdout));
		int	pipefd[2];
		pipe(pipefd);
		// REDIRECT STDOUT TO PIPE ===========
		dup2(pipefd[1], fileno(stdout));
		int res1 = printf(format, '4', "test ft_printf 42", pointer, randomint, -randomint, randomint - 255, randomint - 2048, randomint - 4096);
		fflush(stdout);
		write(pipefd[1], "\0", 1);
		close(pipefd[1]);
		char buffer1[res1 + 1];
  		read(pipefd[0], buffer1, res1);
		buffer1[res1] = '\0';
		// RESTORE STDOUT ====================
		dup2(stdout_bk, fileno(stdout));
		
		pipe(pipefd);
		// REDIRECT STDOUT TO PIPE ===========
		dup2(pipefd[1], fileno(stdout));
		int res2 = ft_printf(format, '4', "test ft_printf 42", pointer, randomint, -randomint, randomint - 255, randomint - 2048, randomint - 4096);
		fflush(stdout);
		write(pipefd[1], "\0", 1);
		close(pipefd[1]);
		char buffer2[res2 + 1];
  		read(pipefd[0], buffer2, res2);
		buffer2[res2] = '\0';
		// RESTORE STDOUT ====================
		dup2(stdout_bk, fileno(stdout));
		
		if (res1 == res2 && strcmp(buffer1, buffer2) == 0)
		{
			setColor(GREEN);
			printf("Test %-3d ", i + 1);
			setColor(BOLD_GREEN);
			printf("[OK]");
			setColor(GREEN);
			printf(" using format : \"%s\"\n", format);
		}
		else
		{
			setColor(RED);
			printf("Test %-3d ", i + 1);
			setColor(BOLD_RED);
			printf("[KO]");
			setColor(RED);
			printf(" using format : \"%s\"\n", format);
			printf("ft_printf printed :%s\n", buffer2);
			printf("returning : %d\n", res2);
			printf("   printf printed :%s\n", buffer1);
			printf("returning : %d\n", res1);
		}
	}
}
