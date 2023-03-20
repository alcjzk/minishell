NAME = 		minishell

OBJ_DIR = 	obj/
INC_DIR = 	inc/ libft/inc/
SRC_DIR = 	$(sort $(dir $(wildcard src/*/))) src/

I =			$(INC_DIR:%=-I%) $(SRC_DIR:%=-I%)
CFLAGS = 	-MP -MMD -Wall -Wextra -Werror $I
LDFLAGS =	-Llibft -lft -lreadline
CC = 		cc

SRCS =\
builtin.c \
builtin_exit.c \
builtin_pwd.c \
builtin_env.c \
ft_isspace.c \
ft_strspn.c \
ft_strcspn.c \
ft_strtonum.c \
ft_strtok.c \
vector.c \
vector_remove.c \
vector_position.c \
shell.c \
main.c

OBJS := 	$(SRCS:%.c=$(OBJ_DIR)%.o)

DEPS = $(SRCS:%.c=$(OBJ_DIR)%.d)

.PHONY: all libft clean fclean re obj_dir

all: $(NAME)

libft:
	make -C libft OBJ_DIR="../obj/"

$(NAME): $(OBJS) | libft
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)%.o: %.c | obj_dir
	$(CC) $(CFLAGS) -c -o $@ $<

obj_dir:
	@mkdir -p $(OBJ_DIR)

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft OBJ_DIR="../obj/"

vpath %.c $(SRC_DIR)

-include $(DEPS)
