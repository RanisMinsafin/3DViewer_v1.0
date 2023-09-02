TEST_LIBS = -lcheck -lm -lpthread
CC = gcc -Wall -Wextra -Werror -std=c11 -g
OS=$(shell uname -s)
LIBS=-lcheck -lm -lpthread
LINUX=-lcheck -lm -lpthread -lrt -lsubunit
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose


all: clean install tests

install:
	make clean
	mkdir build
	cd frontend && qmake && make && make clean && rm Makefile && cd ../ && mv frontend/frontend.app build

uninstall:
	rm -rf build*

clean: uninstall
	rm -rf *.a *.o *.gcda *.gcno *.info test report build* ./frontend/.qmake.stash gcov_test test.out *.dSYM

ifeq ($(OS), Darwin)
dvi:
	open dvi_description/dvi.html
else
dvi:
	echo "open dvi"
endif

dist:
	rm -rf Archive_3d_viewer_v1.0/
	mkdir Archive_3d_viewer_v1.0/ Archive_3d_viewer_v1.0/src Archive_3d_viewer_v1.0/src/frontend Archive_3d_viewer_v1.0/src/dvi_description Archive_3d_viewer_v1.0/src/backend Archive_3d_viewer_v1.0/src/models
	cp Makefile Archive_3d_viewer_v1.0/src
	cp ./dvi_description/*.html Archive_3d_viewer_v1.0/src/dvi_description
	cp ./dvi_description/*.png Archive_3d_viewer_v1.0/src/dvi_description
	cp Makefile *.hpp *.cpp frontend/*.pro frontend/*.cpp frontend/*.ui frontend/*.h  Archive_3d_viewer_v1.0/src/frontend
	cp Makefile ./backend/*.c backend/*.h Archive_3d_viewer_v1.0/src/backend
	cp *.hpp *.cpp *.c  Archive_3d_viewer_v1.0/src
	cp ./models/* Archive_3d_viewer_v1.0/src/models/
	tar cvzf Archive_3d_viewer_v1.0.tgz Archive_3d_viewer_v1.0/
	mv Archive_3d_viewer_v1.0.tgz ../../
	rm -rf Archive_3d_viewer_v1.0/


s21_3d_viewer.a: clean
	$(CC) $(CFLAGS) -c backend/*.c
	ar rcs s21_3d_viewer.a *.o


tests: s21_3d_viewer.a
ifeq ($(OS), Darwin)
	$(CC) unit_tests.c s21_3d_viewer.a -o test.out $(TEST_LIBS)
else
	$(CC) unit_tests.c s21_3d_viewer.a -o test.out $(LINUX)
endif
	./test.out

valgrind_build:  s21_3d_viewer.a
	gcc unit_tests.c -L. -lcheck -lsubunit  s21_3d_viewer.a -lm -ggdb  -o test.out 
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test.out

ifeq ($(OS), Darwin)
gcov_report: s21_3d_viewer.a
	$(CC) $(FLAGS) --coverage unit_tests.c backend/*.c s21_3d_viewer.a $(TEST_LIBS) -o gcov_test
	./gcov_test
	lcov -t "s21_3d_viewer" -o s21_3d_viewer.info -c -d .
	genhtml -o report s21_3d_viewer.info
	open ./report/index.html
else
gcov_report: s21_3d_viewer.a
	$(CC) $(FLAGS) --coverage unit_tests.c backend/*.c s21_3d_viewer.a $(LINUX) -o gcov_test
	./gcov_test
	lcov -t "s21_3d_viewer" -o s21_3d_viewer.info -c -d .
	genhtml -o report s21_3d_viewer.info
	echo "open ./report/index.html in your browser"
endif

clang:
	clang-format --style=google -n */*.c */*.h */*.cpp
