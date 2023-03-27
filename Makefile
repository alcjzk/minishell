# Targets
NAME		= minishell
LIBFT 		= libft/libft.a

# Directories
OBJ_DIR		= obj/
SRC_DIR		= $(sort $(dir $(wildcard src/*/))) src/
INC_DIR		= inc/ libft/inc/ $(SRC_DIR)
LIB_DIR		= libft

# Flags setup
CC		= cc
OPT		= 0
LIB		= readline ft
WARN	= all extra error
EXTRA	= -MP -MMD

# Compiler flags
override CFLAGS 	+= $(EXTRA) $(OPT:%=-O%) $(INC_DIR:%=-I%) $(WARN:%=-W%)
# Linker flags
override LDFLAGS	+= $(LIB_DIR:%=-L%) $(LIB:%=-l%)

# Sources
SRCS =\
builtin.c \
builtin_exit.c \
builtin_pwd.c \
builtin_env.c \
builtin_export.c \
builtin_unset.c \
builtin_cd.c \
ft_isspace.c \
ft_strspn.c \
ft_strcspn.c \
ft_strtonum.c \
ft_strtok.c \
vector.c \
vector_remove.c \
vector_position.c \
shell.c \
env.c \
env_util.c \
env_ops.c \
main.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)

DEPS = $(SRCS:%.c=$(OBJ_DIR)%.d)

.PHONY: all clean fclean re obj_dir $(LIBFT)

all: $(NAME)

$(LIBFT):
	make -C libft OBJ_DIR="../obj/" OPT=$(OPT:%=-O%)

$(NAME): $(OBJS) | $(LIBFT)
	@echo ""
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
	rm -rf $(LIBFT)

debug: fclean
	make -C libft OBJ_DIR="../obj/" FLAGS="-g -fsanitize=address" OPT=$(OPT:%=-O%)
	make $(NAME) CFLAGS="-g -fsanitize=address"

vpath %.c $(SRC_DIR)
-include $(DEPS)
