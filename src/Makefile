CC = gcc 
FLAGS =  -Wall -Werror -Wextra -g# -fsanitize=address -g
LIBRARY = s21_matrix.a
CLEAN = clean
TESTS = TEST/
SRC = $(wildcard *.c)
UNAME := $(shell uname)
SRC_TEST = $(wildcard $(TESTS)*.c)
TARGET = test

ifeq ($(UNAME), Linux)
 TEST_FLAGS += -lcheck -lsubunit -lrt -lpthread -lm
else
 TEST_FLAGS += -lcheck -lm
endif
all : $(CLEAN) $(LIBRARY) $(TARGET)
	$(CLEAN) $(LIBRARY) $(TARGET)
$(TARGET) : $(SRC) $(SRC_TEST)
	$(CC) $(FLAGS) $(SRC_TEST) $(SRC) $(TEST_FLAGS) -o $(TARGET)
	./$(TARGET)
$(LIBRARY) : $(SRC)
	$(CC) $(FLAGS) -c $(SRC) $(TEST_FLAGS)
	ar rc $(LIBRARY) *.o
	ranlib $(LIBRARY)

$(CLEAN) :
	rm -rf $(TARGET) *.a *.o $(TESTS).*o *.out 