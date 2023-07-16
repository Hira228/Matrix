CC = gcc 
FLAGS =  -Wall -Werror -Wextra# -fsanitize=address -g
CLEAN = clean
TESTS = TEST/
SRCS = $(wildcard *.c)
OBJS = ${SRCS:.c = .o}
TEST_OBJS = ${SRCS_TEST:.c = .o}
SRCS_TEST = $(wildcard $(TESTS)*.c)
UNAME := $(shell uname)
TARGET = test
GCOV = gcov_report
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
LIBRARY = s21_matrix.a 

ifeq ($(UNAME), Linux)
 TEST_FLAGS += -lcheck -lsubunit -lrt -lpthread -lm
else
 TEST_FLAGS += -lcheck -lm
endif

%.o: %.c
	${CC} -c ${FLAGS} $@ $<

${TESTS}%.o: ${TESTS}%.c
	${CC} -c ${FLAGS} $@ $< 

all: $(CLEAN) $(LIBRARY) ${SRCS} ${SRCS_TEST} ${GCOV}
	${CC} ${FLAGS} -o ${TARGET} ${SRCS} ${SRCS_TEST} ${TEST_FLAGS}

$(LIBRARY) : $(SRCS)
	$(CC) $(FLAGS) -c $(SRCS) $(TEST_FLAGS)
	ar rc $(LIBRARY) *.o
	ranlib $(LIBRARY)

${GCOV}: build_file
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(SRCS_TEST) $(SRCS) $(TEST_FLAGS) -o Build/${GCOV} 
	Build/./${GCOV} 
	lcov -o ${GCOV}.info -c -d .
	genhtml ${GCOV}.info -o html_report
	open html_report/index.html

build_file:
	mkdir Build

$(CLEAN) :
	rm -rf ${TARGET} *.a *.o $(TESTS).*o *.out app Build *.info html_report TEST/*.o