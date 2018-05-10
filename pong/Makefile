##
## Makefile for pong in /home/samuel/tmp/pong/pong
##
## Made by THOMAS Samuel
## Login   <thomas_s@etna-alternance.net>
##
## Started on  Mon May  7 19:04:47 2018 THOMAS Samuel
## Last update Mon May  7 23:41:28 2018 THOMAS Samuel
##

CC	= @gcc

NAME	= pong

host = $(shell uname)

CFLAGS	= -W -Wall -Werror -Wextra -g3
CFLAGS	+= -I/usr/include/SDL2
CDEBUG	= -g3 -g

LDFLAGS	= -Llib/ -lmy
LDFLAGS=	-L/usr/include/SDL2  -lSDL2 -lSDL2_ttf

ifeq ($(host),Darwin)
LFLAGS = -I include -L lib -l SDL2-2.0.0
endif

SRCS	=	client.c	\
				server.c	\
				main.c

OBJS	= $(SRCS:.c=.o)

MAKELIB	= make -Clib

RM	= @rm -f
ECHO	= echo -e

# Color tags
ECHO=   @echo "\033[0;31;1m"
GECHO=  @echo "\033[0;32;1m"
YECHO=  @echo "\033[0;33;1m"
LBECHO= @echo "\033[0;34;1m"
NCOLOR= @echo "\033[0m"
COLOR_OFF=      \x1b[0m
COLOR=          \x1b[32;01m



all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	$(ECHO) '\033[0;32m> Compiled\033[0m'

clean :
	$(RM) $(OBJS)
	$(ECHO) '\033[0;35m> Directory cleaned\033[0m'

fclean :
	$(GECHO) Cleaning binaries...
	$(RM) $(NAME)
	$(ECHO) '\033[0;35m> Remove executable\033[0m'

debug : $(OBJS)
	$(CC) $(CDEBUG) $(OBJS) -o $(NAME)  $(LDFLAGS)
	$(ECHO) '\033[0;32m> Mode Debug: done\033[0m'

re : fclean all

.PHONY : all clean fclean debug re
