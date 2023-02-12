SRCS	=	$(shell ls ./ | grep .cpp$)

TEST	=	../tests/cavalinho.o

TEST_SRC	=	$(addprefix ../tests/, $(shell ls ../tests/ | grep tests_*))

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	containers

CC 		=	c++

CFLAGS	=	-g3 -Wall -Wextra -Werror -Wshadow -std=c++98

TEST_FLAG = -r compact

ifdef V
	TEST_FLAG += -s -d yes
endif

ifdef STD
	CFLAGS += -D STD
endif

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -rf $(OBJS)
			rm -rf leaks.txt

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

$(TEST):
		c++ -c ../tests/main_t.cpp $< -o $(TEST)

test:	$(TEST)
		$(CC) -g3 $(TEST_SRC) $(TEST) -o ../tests/capivarinha
		@echo
		valgrind --leak-check=full --show-leak-kinds=all --log-file="leaks.txt" ../tests/capivarinha ${TEST_FLAG}

diff:
		@echo
		@echo "ftvector & stdvector"
		@echo
		@diff -y ftvector.txt stdvector.txt
		@echo
		@echo "ftmap & stdmap"
		@echo
		@diff -y ftmap.txt stdmap.txt
		@echo

cleantxt:
		rm -rf ftvector.txt
		rm -rf stdvector.txt
		rm -rf ftmap.txt
		rm -rf stdmap.txt

complete: fclean all
			./$(NAME)
		  make fclean
		  make all STD=1
		  ./$(NAME)
		  make diff