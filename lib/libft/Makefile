# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seheo <seheo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/14 08:55:41 by seheo             #+#    #+#              #
#    Updated: 2022/10/02 15:48:31 by seheo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	libft.a

CC			=	gcc
AR			=	ar rcs
CFLAG		=	-Wall -Wextra -Werror

SRC			=	ft_bzero.c\
				ft_calloc.c\
				ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isdigit.c\
				ft_islower.c\
				ft_isprint.c\
				ft_isupper.c\
				ft_itoa.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_memset.c\
				ft_putchar_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_putstr_fd.c\
				ft_split.c\
				ft_strchr.c\
				ft_strdup.c\
				ft_striteri.c\
				ft_strjoin.c\
				ft_strlcat.c\
				ft_strlcpy.c\
				ft_strlen.c\
				ft_strmapi.c\
				ft_strncmp.c\
				ft_strnstr.c\
				ft_strrchr.c\
				ft_strtrim.c\
				ft_substr.c\
				ft_tolower.c\
				ft_toupper.c\
				ft_strcmp.c\
				ft_double_strlen.c\
				ft_double_strdup.c
				

SRCS_BONUS	=	ft_lstadd_back.c\
				ft_lstadd_front.c\
				ft_lstclear.c\
				ft_lstdelone.c\
				ft_lstiter.c\
				ft_lstlast.c\
				ft_lstmap.c\
				ft_lstnew.c\
				ft_lstsize.c

OBJ_O		=	$(SRC:.c=.o)
OBJ_B		=	$(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
    OBJ_FILES=  $(OBJ_O) $(OBJ_B)
else
    OBJ_FILES = $(OBJ_O)
endif

all		:	$(NAME)

$(NAME)	:	$(OBJ_FILES)
	$(AR) $@ $(OBJ_FILES)

%.o		:	%.c
	$(CC) $(CFLAG) -c $<

clean	:
	rm -f $(OBJ_O) $(OBJ_B)

fclean	:	clean
	rm -f $(NAME) 

re		:	fclean all

bonus	: 	
	make WITH_BONUS=1 all

.PHONY	:	clean fclean re all bonus