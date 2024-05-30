NAME = so_long
LIBFT_NAME = libft
LIBFT_DIR = libft/
INCLUDE_DIR = include/
INCLUDE = -I $(INCLUDE_DIR)
LIBFT_INCLUDE = -I $(LIBFT_DIR)$(INCLUDE_DIR)
SRC_DIR = src/
OBJ_DIR = .obj/
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -L mlx -l mlx -framework OpenGL -framework AppKit
MLX_LINUX_FLAGS = -lmlx_Linux -lXext -lX11

AR = ar
ARFLAGS = rcs
RM = rm -rf
NORM = norminette

MAC_SRC_FILES = main.c

LINUX_SRC_FILES = main_linux.c

SRC_FILES = map.c\
			image.c\
			error.c\
			get_next_str.c

MAC_SRC_FILES += $(SRC_FILES)

LINUX_SRC_FILES += $(SRC_FILES)

MAC_OBJ_FILES = $(MAC_SRC_FILES:%.c=%.o)

LINUX_OBJ_FILES = $(LINUX_SRC_FILES:%.c=%.o)

MAC_SRCS += $(addprefix $(SRC_DIR), $(MAC_SRC_FILES))
MAC_OBJS += $(addprefix $(OBJ_DIR), $(MAC_OBJ_FILES))

LINUX_SRCS += $(addprefix $(SRC_DIR), $(LINUX_SRC_FILES))
LINUX_OBJS += $(addprefix $(OBJ_DIR), $(LINUX_OBJ_FILES))

Y 			= "\033[33m"
R 			= "\033[31m"
G 			= "\033[32m"
B 			= "\033[34m"
X 			= "\033[0m"
UP 			= "\033[A"
CUT 		= "\033[K"

all: $(NAME)

$(NAME): $(OBJ_DIR) $(MAC_OBJS)
	@echo "\n"
	@echo $(B) "--> Into $(LIBFT_DIR)" $(X)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(B) "*** $(NAME) creating ***" $(X)
	$(CC) $(CFLAGS) $(MAC_OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(MLX_FLAGS) -o $(NAME)
	@echo "\n"
	@echo $(G) "!!!!!!! $(NAME) created success !!!!!!!" $(X)

linux: $(OBJ_DIR) $(LINUX_OBJS)
	@echo "\n"
	@echo $(B) "--> Into $(LIBFT_DIR)" $(X)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(B) "*** $(NAME) creating ***" $(X)
	$(CC) $(CFLAGS) $(INCLUDE) $(LINUX_OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(MLX_LINUX_FLAGS) -o $(NAME)
	@echo "\n"
	@echo $(G) "!!!!!!! $(NAME) created success !!!!!!!" $(X)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo $(B) "Compiling $< into $@" $(X)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(R) "<< $(NAME) cleaning>>" $(X)
	$(RM) $(OBJ_DIR)
	@echo "\n"

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(R) "<< $(NAME) fcleaning >>" $(X)
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)
	@echo "\n"

re: fclean all

relinux: fclean linux

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true
	@echo "\n"
	@$(MAKE) -C $(LIBFT_DIR) norm

.PHONY: all clean fclean re norm
