NAME	= spider

SRCS	= main.cpp data_getter.cpp data_parsing.cpp img_data_getter.cpp new_link_handler.cpp utils.cpp 

CC	= c++

OBJS	= $(SRCS:.cpp=.o)

CFLAGS	= -Wall -Wextra -Werror -g3  -Wno-missing-field-initializers

all	:	$(NAME)

%.o	:	%.cpp
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(NAME)	:	$(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $@ -lcurl -ltidy 

clean	:
		rm -rf $(OBJS)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean
		make

.PHONY	:	all fclean clean re
