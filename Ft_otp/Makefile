NAME	= ft_otp 

SRCS	= main.cpp

CC	= c++

OBJS	= $(SRCS:.cpp=.o)

CFLAGS	= -Wall -Wextra -Werror -g3  
all	:	$(NAME)

%.o	:	%.cpp
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 
$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@ -lssl -lcrypto


clean	:
		rm -rf $(OBJS)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean
		make

.PHONY	:	all fclean clean re

