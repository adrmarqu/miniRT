NAME := miniRT
CC := cc
CFLAGS := -Wextra -Wall -Werror -Wunreachable-code -O3 -g
LIBMLX := libs/MLX42
LIBFT := libs/libft
MLX_BUILD := $(LIBMLX)/build
OBJ_D := ./build
SRCSDIR := ./src

INC := ./include/minirt.h
INC += ./include/macros.h
INC += ./include/struct.h
INC += ./include/vector.h
INC += ./include/parser.h

HEADERS := -Iinclude -I$(LIBMLX)/include -I$(LIBFT)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	BREW_PREFIX := $(shell brew --prefix 2>/dev/null)
	ifeq ($(BREW_PREFIX),)
		ifneq ($(wildcard /opt/homebrew),)
			BREW_PREFIX := /opt/homebrew
		else ifneq ($(wildcard /usr/local),)
			BREW_PREFIX := /usr/local
		else ifneq ($(wildcard $(HOME)/.brew),)
			BREW_PREFIX := $(HOME)/.brew
		endif
	endif
	ifneq ($(BREW_PREFIX),)
		HEADERS += -I$(BREW_PREFIX)/include
		LDFLAGS += -L$(BREW_PREFIX)/lib
	endif
	LIBS := $(MLX_BUILD)/libmlx42.a $(LIBFT)/libft.a $(LDFLAGS) -lglfw -framework Cocoa -framework OpenGL -framework IOKit
else
	LIBS := $(MLX_BUILD)/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm
endif

SRCS := main.c free_scene.c print_scene.c mlx_use.c
PARSER := file.c parser_utils.c set_data.c set_setup.c \
	get_objects.c set_aux.c set_objects.c set_utils.c
HIT := intersect_sphere.c intersect_plane.c intersect_cylinder.c intersect_cube.c
RENDER := rendering.c camera.c phong_light.c phong_light_utils.c get_normals.c
VECTOR := vector_op.c vector_op1.c vector_op2.c

OBJS := $(addprefix $(OBJ_D)/, ${SRCS:.c=.o})
OBJS += $(addprefix $(OBJ_D)/render/, ${RENDER:.c=.o})
OBJS += $(addprefix $(OBJ_D)/vector/, ${VECTOR:.c=.o})
OBJS += $(addprefix $(OBJ_D)/parser/, ${PARSER:.c=.o})
OBJS += $(addprefix $(OBJ_D)/intersections/, ${HIT:.c=.o})

all: $(NAME)

$(MLX_BUILD)/libmlx42.a:
	@which cmake > /dev/null 2>&1 || (echo "Error: cmake is required to build MLX42. Run: brew install cmake glfw" && exit 1)
	cmake $(LIBMLX) -B $(MLX_BUILD)
	cmake --build $(MLX_BUILD) -j4

libmlx: $(MLX_BUILD)/libmlx42.a

$(LIBFT)/libft.a:
	make -C $(LIBFT)

libft: $(LIBFT)/libft.a

$(OBJ_D)/%.o: $(SRCSDIR)/%.c Makefile $(INC)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(MLX_BUILD)/libmlx42.a $(LIBFT)/libft.a $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJ_D)
	make clean -C $(LIBFT)

fclean: clean
	rm -rf $(MLX_BUILD)
	make fclean -C $(LIBFT)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx libft
