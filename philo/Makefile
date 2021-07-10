# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avogt <avogt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 11:09:35 by avogt             #+#    #+#              #
#    Updated: 2021/07/10 18:23:31 by avogt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FILES = philo.c \
	error.c \
	free.c \
	parsing.c \
	init.c \
	utils.c \
	actions.c \
	printing_messages.c

FOLDER_SOURCES = srcs
SOURCES_FILES = $(addprefix $(FOLDER_SOURCES)/,$(FILES))
OBJS = $(SOURCES_FILES:.c=.o)

IFLAGS = -I ./include
CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(SOURCES_FILES) -o $(NAME) -lpthread 

%.o: %.c
	@$(CC) $(IFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
