# CC			=	g++  -Wall -Wextra -Werror -fsanitize=address -g

CC			=	g++

TEST_FLAGS	=	-lcheck -lgtest -lgtest_main -lpthread

TESTS_SRC	= 	./tests/s21_test_list.cc ./tests/s21_test_map.cc \
				./tests/s21_test_set.cc ./tests/s21_test_vector.cc ./tests/s21_test_stack.cc \
				./tests/s21_test_queue.cc ./tests/s21_test_array.cc ./tests/s21_test_multiset.cc

all:			leaks

test:			for_test
				./tests/test_result
		 		make clean

leaks: 			for_test
				leaks -atExit -- ./tests/test_result
				make clean


for_test: 		clean
				$(CC) -lgcov -coverage $(TESTS_SRC) $(TEST_FLAGS) -o ./tests/test_result

gcov_report:	clean for_test
				./tests/test_result
				lcov -t "test_result" -o test.info -c -d .
				genhtml -o test_output_list test.info
				@cd ./test_output_list ; open index.html
				rm -rf *.gcno *.gcda

clang:			clean
				cp ../materials/linters/.clang-format ./.clang-format
				clang-format -n --verbose *.h ./tests/*
				clang-format -i *.h ./tests/*
				make clean

clean:
				rm -rf ./a.out* ./.clang-format
				rm -rf *.gcno *.gcda ./tests/test_* ./test_output_list ./test.info
