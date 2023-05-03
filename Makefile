NAME = minishell

UTILS	= utils/create_env.c  utils/env.c  utils/env_clear.c  utils/get_next_line.c  utils/utils.c
SRC		= src/main.c  src/minishell.c  src/prompt.c
EXEC	= exec/built_in/cd.c exec/built_in/echo.c exec/built_in/env.c exec/built_in/exit.c exec/built_in/export.c exec/built_in/export_utils.c exec/built_in/pwd.c exec/built_in/unset.c exec/pipex/exec.c exec/pipex/exec_multiple.c exec/pipex/exec_tools.c exec/pipex/exec_utils.c exec/pipex/signal.c exec/redirect/error.c exec/redirect/here2.c exec/redirect/heredoc.c exec/redirect/redirect.c
PARSING = parsing/check_error_redir2.c parsing/env2.c parsing/exit.c parsing/get_nbre_process.c parsing/get_redirection_type.c parsing/get_token1.c\
		  parsing/interrogation.c parsing/parse.c parsing/put_space_between_redir.c parsing/replace.c parsing/split.c parsing/utils2.c parsing/utils4.c\
		  parsing/check_error_redir.c parsing/env.c parsing/get_functions.c parsing/get_process_1.c parsing/get_tab_redirection.c parsing/get_var_env.c\
		  parsing/lexer.c parsing/parser.c parsing/quotes.c parsing/space_in_var.c parsing/tab_words.c parsing/utils3.c parsing/utils.c

OBJS	= $(SRC:.c=.o)
OTILS	= $(UTILS:.c=.o)
OEXEC	= $(EXEC:.c=.o)
OPARS	= $(PARSING:.c=.o)

RM	= rm -f
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -g3
INC	= -I includes -I utils/ft_printf -I utils/ft_printf/libft
LIBRARY	= -lreadline -lm utils/ft_printf/libftprintf.a -lm utils/ft_printf/libft/libft.a

.c.o:
	${CC} ${CFLAGS} $(INC) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME):	$(OBJS) $(OTILS) $(OEXEC) $(OPARS)
	@make --silent -C utils/ft_printf
	${CC} ${CFLAGS} $^ $(LIBRARY) -o $@

clean:
	$(RM) $(OBJS) $(OTILS) $(OEXEC) $(OPARS)
	@make --silent -C utils/ft_printf clean
	@make --silent -C utils/ft_printf/libft clean

fclean:			clean
				$(RM) $(NAME)
re:				fclean 
	make all

.PHONY:	all clean fclean re
