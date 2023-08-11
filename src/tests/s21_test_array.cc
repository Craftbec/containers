#include <gtest/gtest.h>

#include <array>

#include "../s21_array.h"

using namespace std;
using namespace s21;

TEST(Array, size) {
  Array<int, 3> my_array = {5, 7, 9};
  ASSERT_TRUE(3 == my_array.size());
}

TEST(Array, constructor_empty) {
  Array<int, 3> my_array;
  array<int, 3> array;
  EXPECT_EQ(my_array.size(), array.size());
  EXPECT_EQ(my_array.empty(), array.empty());
}

TEST(Array, constructor_initialization) {
  Array<int, 3> my_array = {5, 7, 9};
  array<int, 3> array = {5, 7, 9};
  auto it = array.begin();
  for (auto m_it = my_array.begin(); m_it != my_array.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Array, constructor_copy) {
  Array<int, 3> tmp = {5, 7, 9};
  Array<int, 3> my_array = tmp;
  array<int, 3> array = {5, 7, 9};
  auto it = array.begin();
  for (auto m_it = my_array.begin(); m_it != my_array.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Array, constructor_move) {
  Array<int, 3> tmp = {5, 7, 9};
  Array<int, 3> my_array = std::move(tmp);
  array<int, 3> array = {5, 7, 9};
  auto it = array.begin();
  for (auto m_it = my_array.begin(); m_it != my_array.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Array, at) {
  Array<int, 3> my_array = {5, 7, 9};
  array<int, 3> array = {5, 7, 9};
  EXPECT_EQ(my_array.at(0), array.at(0));
}

TEST(Array, at2) {
  Array<int, 3> my_array = {5, 7, 9};
  array<int, 3> array = {5, 7, 9};
  EXPECT_EQ(my_array.at(2), array.at(2));
}

// ============= This throw expected test (leak's) ============== //

// TEST(Array, at3) {
//   Array<int, 3> my_array = {5, 7, 9};
//   int A = 1;
//   try {
//     my_array.at(89);
//   } catch (const std::exception& e) {
//     A = 5;
//   }
//   EXPECT_EQ(5, A);
// }

TEST(Array, operator) {
  Array<int, 9> my_array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  array<int, 9> array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  int it = 0;
  int size = my_array.size();
  for (int m_it = 0; m_it < size; it++, m_it++)
    EXPECT_EQ(array[it], my_array[m_it]);
}

TEST(Array, front) {
  Array<int, 9> my_array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  array<int, 9> array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  EXPECT_EQ(array.front(), my_array.front());
}

TEST(Array, back) {
  Array<int, 9> my_array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  array<int, 9> array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  EXPECT_EQ(array.back(), my_array.back());
}

TEST(Array, begin) {
  Array<int, 9> my_array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  array<int, 9> array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  EXPECT_EQ(*array.begin(), *my_array.begin());
}

TEST(Array, empty) {
  Array<int, 9> my_array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  array<int, 9> array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  EXPECT_EQ(array.empty(), my_array.empty());
}

TEST(Array, empty2) {
  Array<int, 9> my_array;
  array<int, 9> array;
  EXPECT_EQ(array.empty(), my_array.empty());
}

TEST(Array, max_size_1) {
  Array<int, 9> my_array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  array<int, 9> array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  EXPECT_EQ(array.max_size(), my_array.max_size());
}

TEST(Array, max_size_2) {
  Array<std::string, 10> my_array = {"1", "2", "3", "4", "5",
                                     "6", "7", "8", "9", "10"};
  array<std::string, 10> array = {"1", "2", "3", "4", "5",
                                  "6", "7", "8", "9", "10"};
  EXPECT_EQ(array.max_size(), my_array.max_size());
}

TEST(Array, swap) {
  Array<int, 9> tmp = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  Array<int, 9> my_array = {5, 5, 5, 5, 5, 5, 5, 5, 5};
  array<int, 9> array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  my_array.swap(tmp);
  auto it = array.begin();
  for (auto m_it = my_array.begin(); m_it != my_array.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Array, fill) {
  Array<int, 9> my_array = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  array<int, 9> array = {5, 5, 5, 5, 5, 5, 5, 5, 5};
  my_array.fill(5);
  auto it = array.begin();
  for (auto m_it = my_array.begin(); m_it != my_array.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}
