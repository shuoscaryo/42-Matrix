CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++14

SRC_FOLDER := src
TESTS_FOLDER := tests

SRC_FILES := Complex.cpp
TPP_FILES := Matrix.tpp Vector.tpp Test.tpp
SRC_CPP := $(addprefix $(SRC_FOLDER)/,$(SRC_FILES))
SRC_TPP := $(addprefix $(SRC_FOLDER)/,$(TPP_FILES))
OBJ := $(SRC_CPP:.cpp=.o)

TEST_CPP := $(wildcard $(TESTS_FOLDER)/*.cpp)
TEST_OBJ := $(TEST_CPP:.cpp=.o)
TEST_EXEC := $(notdir $(TEST_CPP))
TEST_EXEC := $(TEST_EXEC:.cpp=)

all: $(TEST_EXEC)

$(SRC_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	$(CC) $(CFLAGS) -I $(SRC_FOLDER) -c -o $@ $<

$(TESTS_FOLDER)/%.o: $(TESTS_FOLDER)/%.cpp
	$(CC) $(CFLAGS) -I $(SRC_FOLDER) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(TEST_EXEC)

re: fclean all

%: $(TESTS_FOLDER)/%.o $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $< -o $@

.PHONY: all clean fclean re
.SECONDARY: $(OBJ) $(TEST_OBJ) # this is so make doesn't remove the files