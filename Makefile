CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++14

SRC_FOLDER := src
TESTS_FOLDER := tests

SRC_FILES := angle_cos.cpp Complex.cpp lerp.cpp projection.cpp
TPP_FILES := Matrix.tpp Vector.tpp Test.tpp
SRC_CPP := $(addprefix $(SRC_FOLDER)/,$(SRC_FILES))
SRC_TPP := $(addprefix $(SRC_FOLDER)/,$(TPP_FILES))
OBJ := $(SRC_CPP:.cpp=.o)

TEST_CPP := $(wildcard $(TESTS_FOLDER)/*.cpp)
EXEC := $(TEST_CPP:.cpp=)

all:
	echo $(TEST_CPP)

%: $(TESTS_FOLDER)/%.o $(OBJ) $(SRC_TPP)
	$(CC) $(CFLAGS) $(OBJ) $< -o $@

$(SRC_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	$(CC) $(CFLAGS) -I src -c -o $@ $<

$(TESTS_FOLDER)/%.o: $(TESTS_FOLDER)/%.cpp
	$(CC) $(CFLAGS) -I src -c -o $@ $<

clean:
	rm -f $(OBJ) $(TEST_CPP:.cpp=.o)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re
