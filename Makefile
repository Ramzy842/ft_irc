# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 18:50:50 by rchahban          #+#    #+#              #
#    Updated: 2024/05/30 19:06:09 by rchahban         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CPP = c++

# Compiler flags
CPPFLAGS = -Werror -Wall -Wextra -std=c++98

# Source files
SRC = ircserv.cpp Client.cpp Server.cpp

# Object files generated from source files
OBJ = $(SRC:.cpp=.o)

# Name of the ircserv executable to be generated
NAME = ircserv

# Default target to be built
all: $(NAME)

# Rule to generate the ircserv executable from the object files
$(NAME): $(OBJ) irc_serv.hpp Client.hpp Server.hpp
	@$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

# Rule to generate the object files from the source files
%.o: %.cpp irc_serv.hpp Client.hpp Server.hpp
	@$(CPP) $(CPPFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJ)

# Fclean target to remove executable files and finally perform clean
fclean: clean
	rm -f $(NAME)

# Re target to rebuild the project from scratch
re: fclean all

.PHONY: all clean fclean re