.PHONY: all s21_matrix.a test clean build rebuild gcov_report style

CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
FUNC_DIR = functions
COV_FLAGS = -fprofile-arcs -ftest-coverage
TESTFLAGS2 = -lcheck -lm -lpthread -lrt -lsubunit -g

SYSTEM := $(shell uname -s)

ifeq ($(SYSTEM), Linux)
    SYSTEM_FLAGS =  -lcheck -lpthread -lrt -lsubunit -lm
else ifeq ($(SYSTEM), Darwin)
    SYSTEM_FLAGS = -lcheck
endif

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: clean s21_matrix.a

s21_matrix.a: $(OBJS)
	ar rcs $@ $^

test: s21_matrix.a
	$(CC) $(FLAGS) tests/main.c -o  test s21_matrix.a $(SYSTEM_FLAGS)
	./test

testLinux: s21_matrix.a
	$(CC) $(CFLAGS) tests/main.c -o test s21_matrix.a $(TESTFLAGS2)

style: clean
	cp ../materials/linters/.clang-format .
	clang-format -n *.h
	clang-format -n ./functions/*.c
	clang-format -n ./tests/*.c ./tests/*.h
	rm -rf .clang-format

push:
	git add .
	git commit -m "update code based on `date`"
	git push 

gcov_report:
	gcc $(FLAGS) $(COV_FLAGS) $(SRCS) tests/main.c -o test $(SYSTEM_FLAGS)
	./test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	rm -rf *.gc* test coverage.info matrix_test
	open coverage_report/index.html

clean:
	rm -rf s21_matrix.a test $(OBJS)  *.gc* gcov_report coverage.info coverage_report/*
	rm -rf report_html
	rm -rf coverage_report

rebuild: clean s21_matrix.a
