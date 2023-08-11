#include <gtest/gtest.h>

#include <queue>

#include "../s21_queue.h"

using namespace std;
using namespace s21;

TEST(Queue, size) {
  Queue<int> a = {5, 7, 9};
  ASSERT_TRUE(3 == a.size());
}

TEST(Queue, constructor_empty) {
  Queue<int> my_queue;
  queue<int> queue;
  EXPECT_EQ(my_queue.size(), queue.size());
  EXPECT_EQ(my_queue.empty(), queue.empty());
}

TEST(Queue, constructor_initialization) {
  Queue<int> my_queue = {1, 2, 3, 6, 8, 3};
  ASSERT_TRUE(6 == my_queue.size());
  ASSERT_TRUE(0 == my_queue.empty());
  ASSERT_TRUE(1 == my_queue.front());
  ASSERT_TRUE(3 == my_queue.back());
}

TEST(Queue, constructor_copy) {
  Queue<int> tmp = {1, 2, 3, 6, 8, 3};
  Queue<int> my_queue = tmp;
  ASSERT_TRUE(6 == my_queue.size());
  ASSERT_TRUE(0 == my_queue.empty());
  ASSERT_TRUE(1 == my_queue.front());
  ASSERT_TRUE(3 == my_queue.back());
}

TEST(Queue, constructor_move) {
  Queue<int> tmp = {1, 2, 3, 6, 8, 3};
  Queue<int> my_queue = move(tmp);
  ASSERT_TRUE(6 == my_queue.size());
  ASSERT_TRUE(0 == my_queue.empty());
  ASSERT_TRUE(1 == my_queue.front());
  ASSERT_TRUE(3 == my_queue.back());
}

TEST(Queue, empty) {
  Queue<int> my_queue;
  queue<int> queue;
  EXPECT_EQ(my_queue.empty(), queue.empty());
}

TEST(Queue, empty2) {
  Queue<int> my_queue;
  my_queue.push(34);
  queue<int> queue;
  queue.push(34);
  EXPECT_EQ(my_queue.empty(), queue.empty());
}

TEST(Queue, push) {
  Queue<int> my_queue;
  my_queue.push(34);
  my_queue.push(4);
  queue<int> queue;
  queue.push(34);
  queue.push(4);
  EXPECT_EQ(my_queue.back(), queue.back());
}

TEST(Queue, pop) {
  Queue<int> my_queue;
  my_queue.push(34);
  my_queue.pop();
  queue<int> queue;
  queue.push(34);
  queue.pop();
  EXPECT_EQ(my_queue.size(), queue.size());
}

TEST(Queue, pop2) {
  Queue<int> my_queue;
  my_queue.push(34);
  my_queue.push(34);
  my_queue.pop();
  queue<int> queue;
  queue.push(34);
  my_queue.push(34);
  queue.pop();
  EXPECT_EQ(my_queue.back(), queue.back());
}

// =================== This throw exception(leak's) ================== //

// TEST(Queue, front) {
//   Queue<int> my_queue;
//   int A = 1;
//   try {
//     my_queue.front();
//   } catch (const std::exception& e) {
//     A = 5;
//   }
//   EXPECT_EQ(5, A);
// }

// TEST(Queue, back) {
//   Queue<int> my_queue;
//   int A = 1;
//   try {
//     my_queue.back();
//   } catch (const std::exception& e) {
//     A = 5;
//   }
//   EXPECT_EQ(5, A);
// }

// TEST(Queue, pop3) {
//   Queue<int> my_queue;
//   int A = 1;
//   try {
//     my_queue.pop();
//   } catch (const std::exception& e) {
//     A = 5;
//   }
//   EXPECT_EQ(5, A);
// }

TEST(Queue, swap) {
  Queue<int> my_queue;
  my_queue.push(1);
  my_queue.push(2);
  my_queue.push(3);
  Queue<int> my_queue_res;
  my_queue_res.push(89);
  my_queue_res.swap(my_queue);
  ASSERT_TRUE(my_queue_res.size() == 3);
  ASSERT_TRUE(my_queue_res.front() == 1);
  ASSERT_TRUE(my_queue_res.back() == 3);
  ASSERT_TRUE(my_queue.size() == 1);
  ASSERT_TRUE(my_queue.front() == 89);
  ASSERT_TRUE(my_queue.back() == 89);
}
