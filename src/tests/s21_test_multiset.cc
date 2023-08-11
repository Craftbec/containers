#include <gtest/gtest.h>

#include <set>

#include "../s21_multiset.h"

using namespace std;
using namespace s21;

TEST(test_assert, multiset_constructor_std) {
  Multiset<int> A;
  multiset<int> B;
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, multiset_constructor_variable) {
  Multiset<int> A = {{10}, {20}, {30}, {40}};
  multiset<int> B = {{10}, {20}, {30}, {40}};
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, multiset_constructor_copy) {
  Multiset<int> A_1 = {{10}, {20}, {30}, {40}};
  Multiset<int> A(A_1);
  multiset<int> B_1 = {{10}, {20}, {30}, {40}};
  multiset<int> B(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, multiset_constructor_move) {
  Multiset<int> A_1 = {{10}, {20}, {30}, {40}};
  Multiset<int> A(std::move(A_1));
  multiset<int> B_1 = {{10}, {20}, {30}, {40}};
  multiset<int> B(std::move(B_1));
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, multiset_operator_move) {
  Multiset<int> A_1 = {{10}, {20}, {30}, {40}};
  Multiset<int> A = std::move(A_1);
  multiset<int> B_1 = {{10}, {20}, {30}, {40}};
  multiset<int> B = std::move(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, multiset_methods_empty) {
  Multiset<int> A;
  Multiset<int> A_1 = {{10}, {20}, {30}, {40}};
  multiset<int> B;
  multiset<int> B_1 = {{10}, {20}, {30}, {40}};
  ASSERT_EQ(B.empty(), A.empty());
  ASSERT_EQ(B_1.empty(), A_1.empty());
}

TEST(test_assert, multiset_methods_size) {
  Multiset<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Multiset<int> A_1 = {1, 2, 3};
  multiset<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  multiset<int> B_1 = {1, 2, 3};
  ASSERT_FALSE(B.size() == A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

// ============== max_size method test's ================= //

// TEST(test_assert, multiset_methods_max_size_1) {
//   Multiset<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//   multiset<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//   ASSERT_EQ(B.max_size(), A.max_size());
// }

// TEST(test_assert, multiset_methods_max_size_2) {
//   Multiset<std::string> A = {"1", "2", "3", "4", "5", "6", "7", "8", "9",
//   "10"}; multiset<std::string> B = {"1", "2", "3", "4", "5", "6", "7", "8",
//   "9", "10"}; ASSERT_EQ(B.max_size(), A.max_size());
// }

TEST(test_assert, multiset_methods_clear) {
  Multiset<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  multiset<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  A.clear();
  B.clear();
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, multiset_methods_insert) {
  Multiset<int> A = {1, 2, 3};
  multiset<int> B = {1, 2, 3};
  A.insert(8);
  B.insert(8);
  A.insert(777);
  B.insert(777);
  ASSERT_EQ(B.size(), A.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, multiset_methods_erase_1) {
  Multiset<int> A = {0, 1, 2, 3, 4};
  multiset<int> B = {0, 1, 2, 3, 4};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ++it_1;
  ++it_2;
  A.erase(it_1);
  B.erase(it_2);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, multiset_methods_erase_2) {
  Multiset<int> A = {0, 1, 2, 2, 3, 4};
  multiset<int> B = {0, 1, 2, 2, 3, 4};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ++it_1;
  ++it_2;
  ++it_1;
  ++it_2;
  ++it_1;
  ++it_2;
  A.erase(it_1);
  B.erase(it_2);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, multiset_methods_erase_3) {
  Multiset<int> A = {0, 1, 2, 2, 3, 4};
  multiset<int> B = {0, 1, 2, 2, 3, 4};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ++it_1;
  ++it_2;
  ++it_1;
  ++it_2;
  ++it_1;
  ++it_2;
  ++it_1;
  ++it_2;
  ++it_1;
  ++it_2;
  A.erase(it_1);
  B.erase(it_2);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, multiset_methods_erase_4) {
  Multiset<int> A = {0, 1, 2, 3, 4};
  multiset<int> B = {0, 1, 2, 3, 4};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  A.erase(it_1);
  B.erase(it_2);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, multiset_methods_erase_5) {
  Multiset<int> A = {1, 1, 1, 1, 1, 1, 1};
  multiset<int> B = {1, 1, 1, 1, 1, 1, 1};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  for (int i = 0; i < 5; i++, ++it_1, ++it_2)
    ;
  A.erase(it_1);
  B.erase(it_2);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, multiset_methods_swap) {
  Multiset<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Multiset<int> A_1 = {11, 12, 13, 14, 15};
  multiset<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  multiset<int> B_1 = {11, 12, 13, 14, 15};
  A.swap(A_1);
  B.swap(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
  it_1 = A_1.begin();
  it_2 = B_1.begin();
  for (; it_1 != A_1.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, multiset_methods_merge) {
  Multiset<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Multiset<int> A_1 = {11, 12, 13, 14, 15};
  A.merge(A_1);
  ASSERT_EQ(A.size(), 15);
  ASSERT_EQ(A_1.size(), 0);
}

TEST(test_expect, multiset_increments_iterator) {
  Multiset<int> A = {1, 2, 4, 3, 4, 5, 5, 6, 7, 8, 9, 1, 10};
  multiset<int> B = {1, 2, 4, 3, 4, 5, 5, 6, 7, 8, 9, 1, 10};
  ASSERT_EQ(A.size(), B.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    EXPECT_EQ(*it_1, *it_2);
  }
}

TEST(test_expect, multiset_decrements_iterator) {
  Multiset<int> A = {1, 2, 4, 3, 4, 5, 5, 6, 7, 8, 9, 1, 10};
  multiset<int> B = {1, 2, 4, 3, 4, 5, 5, 6, 7, 8, 9, 1, 10};
  ASSERT_EQ(A.size(), B.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  for (size_t i = 1; i < A.size(); ++it_1, ++it_2, i++)
    ;
  for (; it_1 != A.begin(); --it_1, --it_2) {
    EXPECT_EQ(*it_1, *it_2);
  }
  EXPECT_EQ(*it_1, *it_2);
}

TEST(test_assert, multiset_emplace) {
  Multiset<std::string> x = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  auto vt = x.emplace("A", "B", "C");
  ASSERT_TRUE(8 == x.size());
}

TEST(test_assert, multiset_count) {
  Multiset<std::string> x = {"A", "D", "H", "K", "J", "B", "B", "D", "D", "D"};
  multiset<std::string> x_1 = {"A", "D", "H", "K", "J",
                               "B", "B", "D", "D", "D"};
  ASSERT_EQ(x_1.size(), x.size());
  ASSERT_EQ(x_1.count("B"), x.count("B"));
  ASSERT_EQ(x_1.count("D"), x.count("D"));
  ASSERT_EQ(x_1.count("A"), x.count("A"));
  ASSERT_EQ(x_1.count("I"), x.count("I"));
}

TEST(test_assert, multiset_find) {
  Multiset<std::string> x = {"D", "H", "K", "J", "B"};
  multiset<std::string> x_1 = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  auto it = x.find("B");
  auto it_1 = x_1.find("B");
  ASSERT_EQ(*it, "B");
  ASSERT_EQ(*it, *it_1);
}

TEST(test_assert, multiset_contains) {
  Multiset<std::string> x = {"A", "D", "H", "K", "J", "B", "B", "D", "D", "D"};
  ASSERT_EQ(1, x.contains("B"));
  ASSERT_EQ(1, x.contains("D"));
  ASSERT_EQ(1, x.contains("A"));
  ASSERT_EQ(0, x.contains("I"));
}

TEST(test_assert, multiset_equal_range) {
  Multiset<std::string> x = {"A", "D", "H", "K", "J", "B", "B", "D", "D", "D"};
  multiset<std::string> x_1 = {"A", "D", "H", "K", "J",
                               "B", "B", "D", "D", "D"};
  ASSERT_EQ(x_1.size(), x.size());
  ASSERT_EQ(*x_1.equal_range("B").first, *x.equal_range("B").first);
  ASSERT_EQ(*x_1.equal_range("B").second, *x.equal_range("B").second);
  ASSERT_EQ(*x_1.equal_range("D").first, *x.equal_range("D").first);
  ASSERT_EQ(*x_1.equal_range("D").second, *x.equal_range("D").second);
}

TEST(test_assert, multiset_lower_bound) {
  Multiset<std::string> x = {"A", "D", "H", "K", "J", "B", "B", "D", "D", "D"};
  multiset<std::string> x_1 = {"A", "D", "H", "K", "J",
                               "B", "B", "D", "D", "D"};
  ASSERT_EQ(x.size(), x_1.size());
  ASSERT_EQ(*x_1.lower_bound("B"), *x.lower_bound("B"));
  ASSERT_EQ(*x_1.lower_bound("D"), *x.lower_bound("D"));
  ASSERT_EQ(*x_1.lower_bound("A"), *x.lower_bound("A"));
}

TEST(test_assert, multiset_upper_bound) {
  Multiset<std::string> x = {"A", "D", "H", "K", "J", "B", "B", "D", "D", "D"};
  multiset<std::string> x_1 = {"A", "D", "H", "K", "J",
                               "B", "B", "D", "D", "D"};
  ASSERT_EQ(x.size(), x_1.size());
  ASSERT_EQ(*x_1.upper_bound("B"), *x.upper_bound("B"));
  ASSERT_EQ(*x_1.upper_bound("D"), *x.upper_bound("D"));
  ASSERT_EQ(*x_1.upper_bound("A"), *x.upper_bound("A"));
}