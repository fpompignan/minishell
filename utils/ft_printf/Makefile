SRCS	= ft_printf.c pre_determinate.c display/print_hexadecimal.c display/print_simple.c display/print_unsigned.c 
OBJS	= ${SRCS:.c=.o}

NAME	= libftprintf.a

CC	= gcc
AR	= ar rc
RM	= rm -f
RANLIB	= ranlib
CFLAGS = -Wall -Werror -Wextra

.c.o:
	${CC} ${CFLAGS} -c $< -o${<:.c=.o}

${NAME}:	${OBJS}
	@make --silent -C libft
	${AR} ${NAME} ${OBJS} #-lm libft/libft.a
	${RANLIB} ${NAME}

all:	${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
