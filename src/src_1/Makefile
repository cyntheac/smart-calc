#/home/darika/Desktop/Qt_install/6.3.1/gcc_64/bin/qmake
#/Users/girlhasnoname/Qt/6.2.4/macos/bin/qmake

CC = gcc -g
QMAKE_PATH =
LIN_FLAGS = -lcheck
ifeq ($(shell uname), Linux)
LIN_FLAGS += -lpthread -pthread -lrt -lm -lsubunit
endif
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -fprofile-arcs --coverage

TEST_SOURCE = \
	source/backend.c \
	source/calculate.c \
	source/check_input.c \
	source/polish_notation.c \
	source/stack_num.c \
	source/stack_op.c

TEST_OBJ = $(addprefix test/obj/, $(notdir $(TEST_SOURCE:.c=.o)))
	


all: install run

install:
	sh build/script1.sh $(QMAKE_PATH)

run: install
	open calc/./SmartCalc*

uninstall:
	rm -rf calc/*

clean:
	make clean_tests
	rm -rf calc/* build/.*q* \
	build/*.o build/*.h \
	build/*.cpp build/Makefile \
	build/SmartCalc* build/.tmp \
	rm -rf *.gz build/*bak

dvi:
	open doc/doc.pdf

dist:
	sh build/script2.sh

tests: $(TEST_OBJ)
	checkmk clean_mode=1 test/test.check > test/test.c
	$(CC) source/backend.h $(TEST_OBJ) test/test.c -o test/exec $(LIN_FLAGS) $(GCOVFLAGS) $(LDFLAGS)
	test/./exec

clean_tests: 
	rm -rf test/exec* test/test.c
	rm -rf test/obj/* test/coverage*
	rm -rf test/out *gc*

gcov_report:
	make tests
	test/lcov/bin/./lcov -c -d test/obj/. -o test/coverage.info
	test/lcov/bin/./genhtml test/coverage.info --output-directory test/out
	open test/out/index.html

test/obj/%.o: source/%.c source/backend.h
	$(CC) $(GCOVFLAGS) -c $< -o $@

lint:
	python3 ../materials/linters/cpplint.py --extensions=cpp source/mainwindow.cpp \
	source/main.cpp
	python3 ../materials/linters/cpplint.py --extensions=c source/*.c \
	source/backend.h source/mainwindow.h


.PHONY: all install run uninstall clean dvi dist gcov_report clean_tests
