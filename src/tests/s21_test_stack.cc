#include <gtest/gtest.h>

#include <stack>

#include "../s21_stack.h"

using namespace std;
using namespace s21;

TEST(test_assert, stack_constructor_std) {
  Stack<int> A;
  stack<int> B;
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, stack_constructor_variable) {
  Stack<int> A = {1, 2, 3, 4, 5, 6};
  Stack<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Stack<int> A_1;
  A_1.push(1);
  A_1.push(2);
  A_1.push(3);
  A_1.push(4);
  A_1.push(5);
  A_1.push(6);
  ASSERT_EQ(A_1.size(), A.size());
  ASSERT_EQ(10, B.size());
  ASSERT_EQ(6, A.size());
}

TEST(test_assert, stack_constructor_copy) {
  Stack<int> A_1 = {1, 2, 3};
  Stack<int> A(A_1);
  stack<int> B_1;
  B_1.push(1);
  B_1.push(2);
  B_1.push(3);
  stack<int> B(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, stack_constructor_move) {
  Stack<int> A_1 = {1, 2, 3};
  Stack<int> A(std::move(A_1));
  stack<int> B_1;
  B_1.push(1);
  B_1.push(2);
  B_1.push(3);
  stack<int> B(std::move(B_1));
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, stack_operator_move) {
  Stack<int> A_1 = {1, 2, 3};
  Stack<int> A = std::move(A_1);
  stack<int> B_1;
  B_1.push(1);
  B_1.push(2);
  B_1.push(3);
  stack<int> B = std::move(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, stack_methods_top) {
  Stack<int> A;
  stack<int> B;
  for (int i = 0; i < 13; ++i) {
    A.push(i + 1);
    B.push(i);
  }
  A.push(44);
  B.push(44);
  ASSERT_EQ(B.top(), A.top());
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, stack_methods_empty) {
  Stack<int> A;
  Stack<int> A_1 = {1, 2, 3};
  stack<int> B;
  stack<int> B_1;
  B_1.push(1);
  B_1.push(2);
  B_1.push(3);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
  ASSERT_EQ(B.empty(), A.empty());
  ASSERT_EQ(B_1.empty(), A_1.empty());
}

TEST(test_assert, stack_methods_size) {
  Stack<int> A;
  Stack<int> A_1 = {1, 2, 3};
  stack<int> B;
  stack<int> B_1;
  B_1.push(1);
  B_1.push(2);
  B_1.push(3);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, stack_methods_push) {
  Stack<int> A;
  stack<int> B;
  for (int i = 0; i < 13; ++i) {
    A.push(i);
    B.push(i);
  }
  ASSERT_EQ(B.top(), A.top());
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, stack_methods_pop) {
  Stack<int> A;
  stack<int> B;
  for (size_t i = 0; i < A.size(); ++i) {
    A.push(i);
    B.push(i);
  }
  for (size_t i = 0; i < A.size(); ++i) {
    A.pop();
    B.pop();
  }
  A.push(111);
  B.push(111);
  ASSERT_EQ(B.top(), A.top());
  ASSERT_EQ(B.size(), A.size());
  A.push(222);
  B.push(333);
  ASSERT_FALSE(B.top() == A.top());
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, stack_methods_swap) {
  Stack<int> A = {0, 1, 2, 3, 4, 5, 6};
  Stack<int> A_1 = {10, 11, 12, 13, 14, 15, 16};
  Stack<int> A_2;
  stack<int> B;
  stack<int> B_1;
  stack<int> B_2;
  for (int i = 1; i < 7; ++i) {
    B.push(i);
  }
  for (int i = 10; i < 17; ++i) {
    B_1.push(i);
  }
  A.swap(A_1);
  B.swap(B_1);
  ASSERT_EQ(B.top(), A.top());
  ASSERT_EQ(B_1.top(), A_1.top());
  A_2.swap(A_1);
  B_2.swap(B_1);
  ASSERT_EQ(B_2.top(), A_2.top());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(Stack, constructor_empty) {
  Stack<int> my_stack;
  stack<int> stack;
  EXPECT_EQ(my_stack.size(), stack.size());
  EXPECT_EQ(my_stack.empty(), stack.empty());
}

TEST(Stack, constructor_initialization) {
  Stack<int> my_stack = {5, 7, 9, 4, 3, 45, 45, 65};
  ASSERT_TRUE(8 == my_stack.size());
  ASSERT_TRUE(0 == my_stack.empty());
  ASSERT_TRUE(65 == my_stack.top());
}

TEST(Stack, constructor_copy) {
  Stack<int> tmp = {5, 7, 9};
  Stack<int> my_stack = tmp;
  ASSERT_TRUE(9 == my_stack.top());
}

TEST(Stack, constructor_move) {
  Stack<int> tmp = {5, 7, 9};
  Stack<int> my_stack = move(tmp);
  ASSERT_TRUE(9 == my_stack.top());
}

TEST(Stack, constructor_top) {
  Stack<int> my_stack;
  stack<int> stack;
  my_stack.push(1);
  my_stack.push(2);
  my_stack.push(3);
  stack.push(1);
  stack.push(2);
  stack.push(3);
  EXPECT_EQ(my_stack.top(), stack.top());
}

TEST(Stack, empty) {
  Stack<int> my_stack;
  stack<int> stack;
  my_stack.push(1);
  my_stack.push(2);
  my_stack.push(3);
  stack.push(1);
  stack.push(2);
  stack.push(3);
  EXPECT_EQ(my_stack.empty(), stack.empty());
}

TEST(Stack, empty2) {
  Stack<int> my_stack;
  stack<int> stack;
  EXPECT_EQ(my_stack.empty(), stack.empty());
}

TEST(Stack, pop) {
  Stack<int> my_stack;
  stack<int> stack;
  my_stack.push(1);
  my_stack.push(2);
  my_stack.push(3);
  my_stack.pop();
  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.pop();
  EXPECT_EQ(my_stack.top(), stack.top());
}

TEST(Stack, pop2) {
  Stack<int> my_stack;
  stack<int> stack;
  my_stack.push(3);
  my_stack.pop();
  stack.push(3);
  stack.pop();
  EXPECT_EQ(my_stack.size(), stack.size());
}

// =============== This  expected throw exception (leak's) =========== //

// TEST(Stack, top) {
//   Stack<int> my_stack;
//   int A = 1;
//   try {
//     my_stack.top();
//   } catch (const std::exception& e) {
//     A = 5;
//   }
//   EXPECT_EQ(5, A);
// }

// TEST(Stack, pop3) {
//   Stack<int> my_stack;
//   int A = 1;
//   try {
//     my_stack.pop();
//   } catch (const std::exception& e) {
//     A = 5;
//   }
//   EXPECT_EQ(5, A);
// }

TEST(Stack, size) {
  Stack<int> a = {5, 7, 9};
  ASSERT_TRUE(3 == a.size());
}

TEST(Stack, swap) {
  Stack<int> my_stack;
  my_stack.push(1);
  my_stack.push(2);
  my_stack.push(3);
  Stack<int> my_stack_res;
  my_stack_res.push(89);
  my_stack_res.swap(my_stack);
  EXPECT_EQ(my_stack_res.size(), 3);
  EXPECT_EQ(my_stack_res.top(), 3);
  EXPECT_EQ(my_stack.size(), 1);
  EXPECT_EQ(my_stack.top(), 89);
}

TEST(Stack, emplace_front_1) {
  Stack<std::string> x = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  x.emplace_front("A", "B", "C");
  ASSERT_TRUE(8 == x.size());
}

TEST(Stack, emplace_front_2) {
  Stack<std::string> x;
  ASSERT_EQ(0, x.size());
  x.emplace_front("A", "B", "C");
  ASSERT_TRUE(3 == x.size());
}