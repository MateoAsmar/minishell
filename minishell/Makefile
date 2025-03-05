SRCS        = main.c init_datas.c parserutils.c builtins_helper.c ft_cdhelper.c morelexer.c morefuncs.c redirects.c signals.c exec_utils.c helperfunc.c lexer_utils.c checkvarutils.c ft_cd.c ft_echo.c ft_echoutils.c lexer.c execute.c builtins.c parser.c morebuiltins.c minishellutils.c commands.c envtolst.c ft_export.c ft_exportutils.c ft_exportmoreutils.c checkvar.c

OBJS        = $(SRCS:.c=.o)

NAME        = minishell

LIBFT       = Libft/libft.a

CC          = cc
RM          = rm -f

CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -I Libft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) $(INCLUDES) -c $(SRCS) 

$(LIBFT):
		make -C Libft


clean:
	$(RM) $(OBJS)
	make clean -C Libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C Libft

re: fclean all

.PHONY: all clean fclean re
