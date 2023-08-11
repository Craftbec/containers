#include <gtest/gtest.h>

#include <vector>

#include "../s21_vector.h"

using namespace std;
using namespace s21;

TEST(Vector, size) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(my_vector.size(), vector.size());
}

TEST(Vector, constructor_empty) {
  Vector<int> my_vector;
  vector<int> vector;
  EXPECT_EQ(my_vector.size(), vector.size());
  EXPECT_EQ(my_vector.empty(), vector.empty());
}

TEST(Vector, constructor_initialization) {
  Vector<int> my_vector = {5, 7, 9, 4, 3, 45, 45, 65};
  vector<int> vector = {5, 7, 9, 4, 3, 45, 45, 65};
  auto it = vector.begin();
  for (auto m_it = my_vector.begin(); m_it != my_vector.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, constructor_copy) {
  Vector<int> tmp = {5, 7, 9};
  Vector<int> my_vector = tmp;
  vector<int> vector = {5, 7, 9};
  auto it = vector.begin();
  for (auto m_it = my_vector.begin(); m_it != my_vector.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, constructor_move) {
  Vector<int> tmp = {5, 7, 9};
  Vector<int> my_vector = std::move(tmp);
  vector<int> vector = {5, 7, 9};
  auto it = vector.begin();
  for (auto m_it = my_vector.begin(); m_it != my_vector.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, at) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(my_vector.at(0), vector.at(0));
}

// ============= This test with throw exception (leak's) ==============//

// TEST(Vector, at2) {
//   Vector<int> my_vector = {5, 7, 9};
//   int A = 1;
//   try {
//     my_vector.at(-2);
//   } catch (const std::exception& e) {
//     A = 5;
//   }
//   EXPECT_EQ(A, 5);
// }

// TEST(Vector, at3) {
//   Vector<int> my_vector = {5, 7, 9};
//   int A = 1;
//   try {
//     my_vector.at(6);
//   } catch (const std::exception& e) {
//     A = 5;
//   }
//   EXPECT_EQ(A, 5);
// }

TEST(Vector, operator) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(my_vector.size(), vector.size());
  int it = 0;
  int size = my_vector.size();
  for (int m_it = 0; m_it < size; it++, m_it++)
    EXPECT_EQ(my_vector[it], vector[m_it]);
}

TEST(Vector, front) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(my_vector.front(), vector.front());
}

TEST(Vector, front2) {
  Vector<int> my_vector = {5};
  vector<int> vector = {5};
  EXPECT_EQ(my_vector.front(), vector.front());
}

TEST(Vector, back) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(my_vector.back(), vector.back());
}

TEST(Vector, back2) {
  Vector<int> my_vector = {5};
  vector<int> vector = {5};
  EXPECT_EQ(my_vector.back(), vector.back());
}

TEST(Vector, data) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(*my_vector.data(), *vector.data());
}

TEST(Vector, begin) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(*my_vector.begin(), *vector.begin());
}

TEST(Vector, empty) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(my_vector.empty(), vector.empty());
}

TEST(Vector, empty2) {
  Vector<int> my_vector;
  vector<int> vector;
  EXPECT_EQ(my_vector.empty(), vector.empty());
}

TEST(Vector, max_size_1) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(my_vector.max_size(), vector.max_size());
}

TEST(Vector, max_size_2) {
  Vector<std::string> my_vector = {"5", "7", "9"};
  vector<std::string> vector = {"5", "7", "9"};
  EXPECT_EQ(my_vector.max_size(), vector.max_size());
}

TEST(Vector, reserve) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  my_vector.reserve(20);
  vector.reserve(20);
  EXPECT_EQ(my_vector.capacity(), vector.capacity());
}

TEST(Vector, capacity) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  EXPECT_EQ(my_vector.capacity(), vector.capacity());
}

TEST(Vector, shrink_to_fit) {
  Vector<int> my_vector = {5};
  vector<int> vector = {5};
  my_vector.reserve(20);
  vector.reserve(20);
  EXPECT_EQ(my_vector.capacity(), vector.capacity());
  my_vector.shrink_to_fit();
  vector.shrink_to_fit();
  EXPECT_EQ(my_vector.capacity(), vector.capacity());
}

TEST(Vector, clear) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  my_vector.clear();
  vector.clear();
  EXPECT_EQ(my_vector.size(), vector.size());
}

TEST(Vector, insert_1) {
  Vector<int> my_vector = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  vector<int> vector = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  auto m_it = my_vector.begin();
  auto it = vector.begin();
  m_it += 2;
  it += 2;
  my_vector.insert(m_it, 89);
  vector.insert(it, 89);
  it = vector.begin();
  for (auto m_it = my_vector.begin(); m_it != my_vector.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, insert_2) {
  Vector<int> my_vector = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  vector<int> vector = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  auto m_it = my_vector.begin();
  auto it = vector.begin();
  my_vector.insert(m_it, 89);
  vector.insert(it, 89);
  it = vector.begin();
  for (auto m_it = my_vector.begin(); m_it != my_vector.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, erase) {
  Vector<int> my_vector = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  vector<int> vector = {5, 7, 9, 5, 7, 9, 5, 7, 9};
  auto m_it = my_vector.begin();
  auto it = vector.begin();
  m_it++;
  it++;
  my_vector.erase(m_it);
  vector.erase(it);
  it = vector.begin();
  for (auto m_it = my_vector.begin(); m_it != my_vector.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, push_back) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  my_vector.push_back(8);
  vector.push_back(8);
  auto it = vector.begin();
  for (auto m_it = my_vector.begin(); m_it != my_vector.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, push_back2) {
  Vector<int> my_vector;
  vector<int> vector;
  my_vector.push_back(8);
  vector.push_back(8);
  auto it = vector.begin();
  for (auto m_it = my_vector.begin(); m_it != my_vector.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, pop_back) {
  Vector<int> my_vector = {5, 7, 9};
  vector<int> vector = {5, 7, 9};
  my_vector.pop_back();
  vector.pop_back();
  auto it = vector.begin();
  for (auto m_it = my_vector.begin(); m_it != my_vector.end(); it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, swap) {
  Vector<int> my_vector = {5, 7, 9};
  Vector<int> my_vector_tmp = {1, 3};
  vector<int> vector = {5, 7, 9};
  my_vector.swap(my_vector_tmp);
  auto it = vector.begin();
  for (auto m_it = my_vector_tmp.begin(); m_it != my_vector_tmp.end();
       it++, m_it++)
    EXPECT_EQ(*it, *m_it);
}

TEST(Vector, emplace_1) {
  Vector<std::string> x = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  auto it = x.begin();
  it = x.emplace(it, "A", "B", "C");
  it = x.begin();
  ASSERT_EQ(8, x.size());
}

TEST(Vector, emplace_2) {
  Vector<std::string> x = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  auto it = x.begin();
  ++it;
  ++it;
  it = x.emplace(it, "A", "B", "C");
  it = x.begin();
  ASSERT_EQ(8, x.size());
}

TEST(Vector, emplace_3) {
  Vector<std::string> x = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  auto it = x.end();
  it = x.emplace(it, "A", "B", "C");
  it = x.begin();
  ASSERT_EQ(8, x.size());
}

TEST(Vector, emplace_back_1) {
  Vector<std::string> x = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  x.emplace_back("A", "B", "C");
  ASSERT_EQ(8, x.size());
}

TEST(Vector, emplace_back_2) {
  Vector<std::string> x;
  ASSERT_EQ(0, x.size());
  x.emplace_back("A", "B", "C");
  ASSERT_EQ(3, x.size());
}