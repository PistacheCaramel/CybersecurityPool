NAME	= ft_otp

CXX		= c++

CXXFLAGS	= -Wall -Wextra -Werror -MMD -std=c++98 -g3

OPSSLFLAGS = $$(pkg-config --cflags --libs openssl)

SRCS	= main.cpp Crypt.cpp
OBJS	= $(SRCS:.cpp=.o)

DEPS	= $(OBJS:.o=.d)

IFLAGS	= -I.

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -o $@ $^ $(OPSSLFLAGS)

%.o		:	%.cpp
			$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

clean	:
			$(RM) $(DEPS)
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

-include $(DEPS)

.PHONY	:	all fclean clean re
