# $< "include one prerequisite"
# $@ "include target"
# $^ "include the full list of prerequisites)"

SRCS = get_next_line.c get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g3

NAME = gnl.a

$(NAME): $(OBJS)
	@@ar -rsc $@ $^
	@echo gnl.a created!

all : $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re