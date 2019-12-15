# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfrias <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/29 17:06:24 by mfrias            #+#    #+#              #
#    Updated: 2019/05/22 15:20:49 by mfrias           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
CFLAG = -Wall -Wextra -Werror
SUBDIR = libft/
SRC = ./*.c
HDR = ./*.o
ARCHIVE = libft/libft.a

all: $(NAME)

$(NAME):
	make -C $(SUBDIR)
	gcc $(CFLAG) -o $(NAME) $(SRC) -I $(HDR) -L. $(ARCHIVE)

clean:
	rm -f *.o
	make -C $(SUBDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f fillit.a
	make -C $(SUBDIR) fclean

re: fclean all

