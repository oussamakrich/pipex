# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okrich <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 12:15:29 by okrich            #+#    #+#              #
#    Updated: 2023/01/11 19:27:58 by okrich           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
 
CFLAGS = -Wall -Werror -Wextra

NAME = pipex

NAME_BNS = pipexbonus

SRC = main pipex_utils ft_split ft_split_utils

SRC_BONUS = pipex_bonus utils_bonus ft_split ft_split_utils\
			pipex_utils get_next_line utils_heredoc ft_itoa

OBJ = $(addsuffix .o, $(SRC))

OBJ_BNS = $(addsuffix .o, $(SRC_BONUS))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

bonus : $(NAME_BNS)

$(NAME_BNS) : $(OBJ_BNS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c pipex.h
	$(CC) $(CFLAGS) -c $<

clean :
	@rm -f $(OBJ)
	@rm -f $(OBJ_BNS)

fclean : clean
	@rm -f $(NAME)
	@rm -f $(NAME_BNS)

re : fclean all
