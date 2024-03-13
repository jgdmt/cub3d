SRCS			:=	main.c cast.c free.c parsing.c parsing_get.c parsing_utils.c events.c
# SRCS_BUILTINS	:=	env.c cd.c pwd.c export_utils.c export.c export_add.c export_parsing.c export_print.c unset.c echo.c exit.c
# SRCS_PARSING	:=	parsing_env_utils.c lexer.c lexer_utils.c expander.c parser.c parser_utils.c here_doc.c here_doc_utils.c checker.c checker_utils.c
# SRCS_EXEC		:=	exec.c exec_utils.c pipex.c
OBJS			:= $(SRCS:.c=.o)
# OBJS_PARSING	:= $(addprefix parsing/,$(SRCS_PARSING:.c=.o))
# OBJS_BUILTINS	:= $(addprefix builtins/,$(SRCS_BUILTINS:.c=.o))
# OBJS_PIPEX		:= $(addprefix pipex/,$(SRCS_PIPEX:.c=.o))
# OBJS_EXEC		:= $(addprefix exec/,$(SRCS_EXEC:.c=.o))
CC				:= cc
RM				:= rm -rf
CFLAGS			:= -Wall -Wextra -Werror  -I. -ggdb3 #-fsanitize=address
MLXFLAGS		:= -framework Cocoa -framework OpenGL -framework IOKit  -L "/Users/$(USER)/.brew/opt/glfw/lib/" -I MLX42/include -lglfw
NAME			:= cub3d

all:			libmlx $(NAME) 

libmlx:
	@cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4

$(NAME):		$(OBJS) 
				$(MAKE) bonus -C ./libft
				$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJS) libft/libft.a MLX42/build/libmlx42.a

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJS)
				$(RM) MLX42/build

fclean:			clean
				$(MAKE) fclean -C ./libft
				$(RM) $(NAME)
				$(RM) $(NAME_BONUS)

re:				fclean libmlx $(NAME)

.PHONY:			all clean fclean re bonus
# .SILENT:

