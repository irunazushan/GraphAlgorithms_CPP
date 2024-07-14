CXX = g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++17
LTEST = -lgtest
GCOVFLAGS = --coverage

TEST_DIR = tests
LIB_GRAPH = lib_graph/s21_graph.a
LIB_GRAPH_ALGORITHMS = lib_graph_algorithms/s21_graph_algorithms.a
LIB_QUEUE = lib_queue/s21_queue.a
LIB_STACK = lib_stack/s21_stack.a

SRC = $(wildcard lib_graph/*.cc lib_graph_algorithms/*.cc lib_queue/*.cc lib_stack/*.cc)
OBJS = $(SRC:.cc=.o)

OS := $(shell uname -s)

ifeq ($(OS),Linux)
	OPEN_CMD := xdg-open
else ifeq ($(OS),Darwin)
	OPEN_CMD := open
endif

.PHONY: all main

all: clean s21_queue s21_stack s21_graph s21_graph_algorithms test

run: clean s21_queue s21_stack s21_graph s21_graph_algorithms main

main: $(LIB_QUEUE) $(LIB_STACK) $(LIB_GRAPH) $(LIB_GRAPH_ALGORITHMS) 
	$(CXX) $(CXXFLAGS) view/*.cc $^ -o main
	./main

test: $(LIB_QUEUE) $(LIB_STACK) $(LIB_GRAPH) $(LIB_GRAPH_ALGORITHMS)
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/*.cc $^ -o test $(LTEST)
	./test

gcov_report: $(LIB_QUEUE) $(LIB_STACK)
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) lib_graph/*.cc lib_graph_algorithms/*.cc $(TEST_DIR)/*.cc $^ -o test $(LTEST) $(LIBS)
	./test
	lcov --ignore-errors inconsistent -t "Report" -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	rm -rf *.gcno *.gcov *.gcda *.info *.a *.dSYM tests/*.o
	$(OPEN_CMD) ./report/index.html

s21_graph: $(OBJS)
	ar rcs $(LIB_GRAPH) $^

s21_graph_algorithms: $(OBJS)
	ar rcs $(LIB_GRAPH_ALGORITHMS) $^

s21_queue: $(OBJS)
	ar rcs $(LIB_QUEUE) $^

s21_stack: $(OBJS)
	ar rcs $(LIB_STACK) $^

leak:
	leaks -atExit -- ./test

valg:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

clang:
	clang-format -i --style=Google **/*.cc **/*.h

clean:
	rm -rf main test lib_graph/*.o lib_graph/*.a lib_graph_algorithms/*.o lib_graph_algorithms/*.a
	rm -rf main test lib_stack/*.o lib_stack/*.a lib_queue/*.o lib_queue/*.a
	rm -rf report