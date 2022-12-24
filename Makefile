NAME			= minishell

CC				= cc
CFLAGS			= 
#-g3 -fsanitize=address -Wall -Wextra -Werror
RM				= rm -rf

LIB_READ		= -l readline
READLINE		= -L$(shell brew --prefix readline)/lib
READLINE_INC	= -I$(shell brew --prefix readline)/include

LIB_DIR			= lib/
LIBFT			= libft/libft.a
HEADERS			= include

MAIN			= main
UTIL			= get_env dictionary deque/deque deque/deque_util
PARSER			= lexer token

SRCS 			= $(addsuffix .c, $(addprefix src/, $(MAIN)))			\
				$(addsuffix .c, $(addprefix src/util/, $(UTIL)))		\
				$(addsuffix .c, $(addprefix src/parser/, $(PARSER)))

OBJS 			= $(SRCS:c=o)


# ================ Color Variables ================ #
RED				=	"\033[0;31m"
GREEN			=	"\033[0;32m"
YELLOW			=	"\033[1;33m"
EOC				=	"\033[0;0m"
# ================================================= #

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GREEN) "Source files are compiled!\n" $(EOC)
	@make bonus -j -C $(LIB_DIR)/libft
	@$(CC) $(CFLAGS) -o $@ $^ $(LIB_DIR)/$(LIBFT) $(LIB_READ) $(READLINE) $(READLINE_INC)
	@echo $(GREEN) "$(NAME) is created!\n" $(EOC)

%.o: %.c $(HEADERS)/$(NAME).h
	@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)
	@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@make -j clean -C $(LIB_DIR)/libft
	@$(RM) $(OBJS)
	@echo $(RED) "Object file clean!\n" $(EOC)

fclean:	clean
	@make -j fclean -C $(LIB_DIR)/libft
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) is removed!\n\n" $(EOC)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
