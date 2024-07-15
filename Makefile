# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaidriss <yaidriss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 18:50:50 by rchahban          #+#    #+#              #
#    Updated: 2024/07/15 11:55:42 by yaidriss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CPP = c++

# Compiler flags
CPPFLAGS = -Werror -Wall -Wextra -std=c++98

# Source files
SRC = ircserv.cpp Client.cpp Server.cpp Channel.cpp commands/cmd.cpp commands/topic.cpp commands/invite.cpp commands/utils.cpp commands/kick.cpp commands/mode.cpp commands/pass.cpp commands/nick.cpp

# Object files generated from source files
OBJ = $(SRC:.cpp=.o)

# Name of the ircserv executable to be generated
NAME = ircserv

# Default target to be built
all: $(NAME)

# Rule to generate the ircserv executable from the object files
$(NAME): $(OBJ) irc_serv.hpp Client.hpp Server.hpp  Channel.hpp commands/cmd.hpp commands/topic.hpp commands/invite.hpp
	@ $(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[92m░░███╗░░██████╗░██████╗░███████╗\033[0m███╗░░░███╗███████╗██████╗░"
	@echo "\033[92m░████║░░╚════██╗╚════██╗╚════██║\033[0m████╗░████║██╔════╝██╔══██╗"
	@echo "\033[92m██╔██║░░░█████╔╝░█████╔╝░░░░██╔╝\033[0m██╔████╔██║█████╗░░██║░░██║"
	@echo "\033[92m╚═╝██║░░░╚═══██╗░╚═══██╗░░░██╔╝░\033[0m██║╚██╔╝██║██╔══╝░░██║░░██║"
	@echo "\033[92m███████╗██████╔╝██████╔╝░░██╔╝░░\033[0m██║░╚═╝░██║███████╗██████╔╝"
	@echo "\033[92m╚══════╝╚═════╝░╚═════╝░░░╚═╝░░░\033[0m╚═╝░░░░░╚═╝╚══════╝╚═════╝░"
	@echo "\033[92mCREATING .O FILES AND exuctubel of $(NAME) ⌛\033[0m"
	@echo "\033[93mIRC SERVER IS READY TO USE 🚀\033[0m"
# Rule to generate the object files from the source files
%.o: %.cpp irc_serv.hpp Client.hpp Server.hpp Channel.hpp commands/cmd.hpp
	@ $(CPP) $(CPPFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	@rm -f $(OBJ)
	@echo "\033[31m Delete object files🗑\033[31m"

# Fclean target to remove executable files and finally perform clean
fclean: clean
	@rm -f $(NAME)
	@echo "\033[31m Delete exucted file🗑\033[31m"
# Re target to rebuild the project from scratch
re: fclean all

.PHONY: all clean fclean re