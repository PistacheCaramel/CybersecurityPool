NAME	= spider

SRCS	= main.cpp

CC	= c++

OBJS	= $(SRCS:.cpp=.o)

CFLAGS	= -Wall -Wextra -Werror -g3

INCLUDES = -I/usr/include/libxml2
all	:	$(NAME)

%.o	:	%.cpp
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
