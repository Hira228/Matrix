CC = gcc 
FLAGS = -Wall -Werror -Wextra #-fsanitize=address -g
LIBRARY = s21_matrix.a
CLEAN = clean
REPORT = gcov_report
TESTS = ./TESTS/
SRC = $(wildcard *.c)
UNAME := $(shell uname)
SRC_TEST = $(wildcard $(TESTS)*.c)
TARGET = test
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov 

ifeq ($(UNAME), Linux)
 TEST_FLAGS += -lcheck -lsubunit -lrt -lpthread -lm
else
 TEST_FLAGS += -lcheck -lm
endif
all : $(CLEAN) $(LIBRARY) $(TARGET) $(REPORT)
	$(CLEAN) $(LIBRARY) $(TARGET) $(REPORT)
$(TARGET) : $(SRC) $(SRC_TEST)
	$(CC) $(FLAGS) $(SRC_TEST) $(SRC) $(TEST_FLAGS) -o $(TARGET)
	./$(TARGET)
$(LIBRARY) : $(SRC)
	$(CC) $(FLAGS) -c $(SRC) $(TEST_FLAGS)
	ar rc $(LIBRARY) *.o
	ranlib $(LIBRARY)

$(REPORT) : $(SRC) $(SRC_TEST) build_file
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(SRC_TEST) $(SRC) $(TEST_FLAGS) -o Build/$(REPORT)
	Build/./$(REPORT)
	lcov -o $(REPORT).info -c -d .
	genhtml $(REPORT).info -o html_report
	open html_report/index.html

build_file:
	mkdir Build
$(CLEAN) :
	rm -rf Build $(TARGET) *.a *.o $(TESTS).*o ./html_report/ gcov_report *.gcno *.gcda *.info *.out 