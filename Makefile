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
#    Updated: 2019/10/06 15:16:25 by mfaussur    |____\_, \___/_||_| |_|       #
#                                                     /__/            .fr      #
# **************************************************************************** #

APP					= compiler
gcc					= gcc
LD					= gcc
CFLAGS				= -Wall -pipe
OFLAGS				= -Werror -Wextra -Wall -c -I./include
SOURCES				= $(wildcard source/*.c)
OBJECTS				= $(SOURCES:.c=.o)
DEBUG				= no
PROFILE				= no
PEDANTIC			= no
OPTIMIZATION		= -O3

ifeq ($(DEBUG), yes)
	CFLAGS			+= -g
	OPTIMIZATION	= -O0
endif

ifeq ($(PROFILE), yes)
	CFLAGS			+= -pg
endif

CFLAGS				+= $(OPTIMIZATION)

all:				main

main:				$(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(APP)

%.o:				%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o

fclean:
	rm -f $(APP)

rebuild:			clean fclean all

.PHONY :			clean

.SILENT :			clean
