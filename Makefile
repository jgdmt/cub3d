SRCS			:=	main.c test.c
# SRCS_BUILTINS	:=	env.c cd.c pwd.c export_utils.c export.c export_add.c export_parsing.c export_print.c unset.c echo.c exit.c
# SRCS_PARSING	:=	parsing_env_utils.c lexer.c lexer_utils.c expander.c parser.c parser_utils.c here_doc.c here_doc_utils.c checker.c checker_utils.c
# SRCS_EXEC		:=	exec.c exec_utils.c pipex.c
OBJS			:= $(SRCS:.c=.o)
# OBJS_PARSING	:= $(addprefix parsing/,$(SRCS_PARSING:.c=.o))
# OBJS_BUILTINS	:= $(addprefix builtins/,$(SRCS_BUILTINS:.c=.o))
# OBJS_PIPEX		:= $(addprefix pipex/,$(SRCS_PIPEX:.c=.o))
# OBJS_EXEC		:= $(addprefix exec/,$(SRCS_EXEC:.c=.o))
CC				:= gcc
RM				:= rm -f
CFLAGS			:= -Wall -Wextra -Werror  -I. #-ggdb3 -fsanitize=address
MLXFLAGS		:= -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
NAME			:= minishell

all:			$(NAME) libmlx

libmlx:
	@cmake 42MLX -B 42MLX/build && make -C 42MLX/build -j4

$(NAME):		$(OBJS) 
				$(MAKE) bonus -C ./libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a MLX42/build/libmlx42.a

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJS)
				$(RM) 42MLX/build

fclean:			clean
				$(MAKE) fclean -C ./libft
				$(RM) $(NAME)
				$(RM) $(NAME_BONUS)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus
# .SILENT:

