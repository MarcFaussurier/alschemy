# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    Authors: mfaussur                              +:+   +:    +:    +:+      #
#    <marc.faussurier@etu.univ-lyon1.fr>           #+#   #+    #+    #+#       #
#                                                 #+#   ##    ##    #+#        #
#                                                ###    #+./ #+    ###.fr      #
#                                                         /   UNIV -           #
#                                                | |  _  / ___ _ _   / |       #
#    Created: 2019/10/06 11:23:52 by mfaussur    | |_| || / _ \ ' \  | |       #
#    Updated: 2019/11/13 10:12:32 by mfaussur    |____\_, \___/_||_| |_|       #
#                                                     /__/            .fr      #
# **************************************************************************** #

CSRC		:=	./lexer.c			\
				./parser.c			\
				./evaluator.c		\
				./main.c
NAME		:= alschemy
DEBUG		:= 0
RM			:= rm -rf
AR			:= ar rcs
CC			:= gcc
CFLAGS		:= -Werror -Wextra -Wall -I./libft
COBJ		:= $(CSRC:.c=.o)
DEBUGFLAGS	:= -g -fsanitize=address -fno-omit-frame-pointer
INC			:= ./
CFLAGS		:= $(CFLAGS) -I$(INC)
ifeq ($(DEBUG),1)
CFLAGS		+= $(DEBUGFLAGS)
endif

all:		$(NAME)
clean:
	$(RM) $(COBJ) $(BONUSOBJ)
fclean:		clean
	$(RM) $(NAME)
re:		fclean all
norme:
	norminette
bonus:		$(COBJ) $(BONUSOBJ)
	$(AR) $(NAME) $(COBJ) $(BONUSOBJ)
%.o:	%.c		scheme.h
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME):	$(COBJ)
	cd libft && make bonus;
	$(CC) -o $(NAME) $(COBJ) -L./libft -lft
.PHONY:
	all fclean clean re bonus
