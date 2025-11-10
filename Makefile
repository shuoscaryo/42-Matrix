NAME := #NAME

CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++14

SRC := main.cpp

OBJ := $(SRC:.cpp=.o)

# If no name provided, set default a.out
ifeq ($(NAME),)
	NAME := a.out
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

ex%:
	$(DOCKER_COMPOSE) exec $* sh

.PHONY: clean fclean all re
