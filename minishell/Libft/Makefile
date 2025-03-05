SRCS       = ft_atoi.c clean_args.c quote.c safe_strjoin.c ft_bzero.c ft_strtol.c ft_atol.c 2darraysize.c ft_calloc.c ft_strncpy.c ft_strstr.c ft_remove_chars.c addstring.c ft_strcpy.c ft_isalnum.c ft_strndup.c ft_isspace.c ft_strcmp.c ft_isalpha.c ft_doublelength.c freearray.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

OBJS        = ${SRCS:.c=.o}

NAME        = libft.a

CC          = cc
RM          = rm -f
AR          = ar rc
RN          = ranlib

CFLAGS      = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}
			${RN} ${NAME}

all: $(NAME)

clean:
	${RM} ${OBJS} ${B_OBJS}

fclean:	clean
		${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re