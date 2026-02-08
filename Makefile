CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++14

SRC_FOLDER := src
TESTS_FOLDER := tests

SRC_FILES := Complex.cpp Test.cpp
TPP_FILES := Matrix.tpp Vector.tpp Test.tpp
SRC_CPP := $(addprefix $(SRC_FOLDER)/,$(SRC_FILES))
SRC_TPP := $(addprefix $(SRC_FOLDER)/,$(TPP_FILES))
OBJ := $(SRC_CPP:.cpp=.o)

TEST_CPP := $(wildcard $(TESTS_FOLDER)/*.cpp)
TEST_OBJ := $(TEST_CPP:.cpp=.o)
TEST_NAMES := base ex00 ex01 ex02 ex03 ex04 ex05 ex06 ex07 ex08 ex09 ex10 ex11\
	ex12 ex13 ex14 ex15

all: $(TEST_NAMES)

$(SRC_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp $(SRC_TPP)
	$(CC) $(CFLAGS) -I $(SRC_FOLDER) -c -o $@ $<

$(TESTS_FOLDER)/%.o: $(TESTS_FOLDER)/%.cpp $(SRC_TPP)
	$(CC) $(CFLAGS) -I $(SRC_FOLDER) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(TEST_NAMES)

re: fclean all

# links the test name to the .o with the %
$(TEST_NAMES): %: $(TESTS_FOLDER)/%.o $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $< -o $@	

.PHONY: all clean fclean re
.SECONDARY: $(OBJ) $(TEST_OBJ) # this is so make doesn't remove the files