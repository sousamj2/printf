#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marisous <marisous@student.42lisb...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/05 11:20:42 by marisous          #+#    #+#              #
#    Updated: 2026/11/26 14:52:55 by marisous         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC	= cc
CFLAGS	= -Wall -Wextra $(addprefix -I, $(INC_FOLDERS))
CFLAGS	+= -g -O0

NAME	= libprintf.a

SRC_FOLDER_1	= libft
SRC_FOLDER_2	= .


OBJ_FOLDER	= objs

PART_1	= 	strlen memset bzero toupper tolower \
		strnstr atoi calloc isdigit atoi strlcpy \
		strdup itoa putchar_fd putstr_fd strncmp	

PART_2	= 	ibasetoa max putchars_n_fd putstr_fd_n striter printf

SRCS1	=	$(addsuffix .c, $(addprefix ft_, $(PART_1)))
SRCS2	=	$(addsuffix .c, $(addprefix ft_, $(PART_2)))
SRCS	=	$(addprefix $(SRC_FOLDER_1)/, $(SRCS1))	\
		$(addprefix $(SRC_FOLDER_2)/, $(SRCS2)) 
OBJS	= 	$(addprefix $(OBJ_FOLDER)/, 	$(SRCS1:.c=.o) \
						$(SRCS2:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@# r for insert/[r]eplace object files.
	@# c for [c]reating the file if it does not exist.
	@# s create the [s]ymbol index.
	ar rcs $(NAME) $(OBJS)

objs/%.o: $(SRC_FOLDER_1)/%.c 
	@mkdir -p objs/
	$(CC) $(CFLAGS) -c $^ -o $@
objs/%.o: $(SRC_FOLDER_2)/%.c
	@mkdir -p objs/
	$(CC) $(CFLAGS) -c $^ -o $@

clean: 
	rm -rf $(OBJ_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: main.c $(NAME)
	$(CC) $(CFLAGS) $^ -o run

.PHONY: all clean fclean re test test_% norm unitests eclean

test:
	@echo NAME=$(NAME)
	@echo OBJS=$(OBJS)
	@echo SRCS=$(SRCS)

norm:
	norminette $(SRCS) libft.h | grep -v ": OK!" # ; status=$${PIPESTATUS[0]} ; exit $$status	
	@echo Norminette: all OK!
	@echo "Number of functions: mine: 43 | theirs: $$(ls -1 ft*.c | wc -l)"
	@echo "Static functions: mine: 7 | theirs: $$(grep -l '\bstatic\b' *.c | wc -l)"
	@echo "Includes: $$(grep include $(SRCS) | grep -v libft.h)"
	@for f in *.c; do \
		count=$$(ctags -x --c-kinds=f "$$f" | wc -l); \
		if [ "$$count" -gt 1 ]; then \
			printf "%-20s %s\n" "$$f" "$$count"; \
		fi; \
	done

eclean:
	rm -fv compile_commands.json
	bear -- make
	$(MAKE) fclean
