
NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = 	args_to_str.c		\
		ft_atoi.c			\
		ft_isdigit.c		\
		ft_itoa_base.c		\
		ft_printf.c			\
		ft_putstr_fd.c		\
		ft_straddchr.c		\
		ft_strcat_malloc.c	\
		ft_strchr.c			\
		ft_strlcat.c		\
		ft_strlcpy.c		\
		ft_strlen.c			\
		ft_substr.c			\
		ft_toupper.c		\
		print_arg.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I include -c $< -o $@

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all