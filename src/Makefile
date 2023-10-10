NAME	= spider

SRCS	= main.c data_getter.c data_parsing.c

CC	= gcc

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -g3

INCLUDES = -I/usr/include/libxml2
all	:	$(NAME)

%.o	:	%.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@ -lcurl -lxml2

clean	:
		rm -rf $(OBJS)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean
		make

.PHONY	:	all fclean clean re
