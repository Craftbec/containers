#include <gtest/gtest.h>

#include <set>

#include "../s21_set.h"
#include "../s21_vector.h"

using namespace std;
using namespace s21;

TEST(test_assert, set_constructor_std) {
  Set<int> A;
  set<int> B;
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, set_constructor_variable) {
  Set<int> A = {{10}, {20}, {30}, {40}};
  set<int> B = {{10}, {20}, {30}, {40}};
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, set_constructor_copy) {
  Set<int> A_1 = {{10}, {20}, {30}, {40}};
  Set<int> A(A_1);
  set<int> B_1 = {{10}, {20}, {30}, {40}};
  set<int> B(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, set_constructor_move) {
  Set<int> A_1 = {{10}, {20}, {30}, {40}};
  Set<int> A(std::move(A_1));
  set<int> B_1 = {{10}, {20}, {30}, {40}};
  set<int> B(std::move(B_1));
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, set_operator_move) {
  Set<int> A_1 = {{10}, {20}, {30}, {40}};
  Set<int> A = std::move(A_1);
  multiset<int> B_1 = {{10}, {20}, {30}, {40}};
  multiset<int> B = std::move(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, set_methods_empty) {
  Set<int> A;
  Set<int> A_1 = {{10}, {20}, {30}, {40}};
  set<int> B;
  set<int> B_1 = {{10}, {20}, {30}, {40}};
  ASSERT_EQ(B.empty(), A.empty());
  ASSERT_EQ(B_1.empty(), A_1.empty());
}

TEST(test_assert, set_methods_size) {
  Set<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Set<int> A_1 = {1, 2, 3};
  set<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  set<int> B_1 = {1, 2, 3};
  ASSERT_FALSE(B.size() == A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

// ============== max_size method test's ================= //

// TEST(test_assert, set_methods_max_size_1) {
//   Set<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//   set<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//   ASSERT_EQ(B.max_size(), A.max_size());
// }

// TEST(test_assert, set_methods_max_size_2) {
//   Set<std::string> A = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
//   set<std::string> B = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
//   ASSERT_EQ(B.max_size(), A.max_size());
// }

TEST(test_assert, set_methods_clear) {
  Set<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  set<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  A.clear();
  B.clear();
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, set_methods_insert) {
  Set<int> A = {1, 2, 3};
  set<int> B = {1, 2, 3};
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

TEST(test_assert, set_methods_erase_1) {
  Set<int> A = {0, 1, 2, 3, 4};
  set<int> B = {0, 1, 2, 3, 4};
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

TEST(test_assert, set_methods_erase_2) {
  Set<int> A = {0, 1, 2, 2, 3, 4};
  set<int> B = {0, 1, 2, 2, 3, 4};
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

TEST(test_assert, set_methods_erase_3) {
  Set<int> A = {0, 1, 2, 2, 3, 4};
  set<int> B = {0, 1, 2, 2, 3, 4};
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
  A.erase(it_1);
  B.erase(it_2);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, set_methods_erase_4) {
  Set<int> A = {0, 1, 2, 3, 4};
  set<int> B = {0, 1, 2, 3, 4};
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

TEST(test_assert, set_methods_erase_5) {
  for (int i = 0; i < 17; ++i) {
    Set<int> A = {12, 0,  13, 18, 15,  24, 14, 17, 16,
                  20, 30, 22, 10, -10, -5, 8,  -15};
    auto it = A.begin();
    for (int j = 0; j < i; ++j, ++it)
      ;
    if (it != nullptr && *it != 18) {
      A.erase(it);
    }
  }
}

TEST(test_assert, set_methods_swap) {
  Set<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Set<int> A_1 = {11, 12, 13, 14, 15};
  set<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  set<int> B_1 = {11, 12, 13, 14, 15};
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

TEST(test_assert, set_methods_merge) {
  Set<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Set<int> A_1 = {11, 12, 13, 14, 15};
  A.merge(A_1);
  ASSERT_EQ(A.size(), 15);
  ASSERT_EQ(A_1.size(), 0);
}

TEST(test_expect, set_increments_iterator) {
  Set<int> A = {1, 2, 4, 3, 4, 5, 5, 6, 7, 8, 9, 1, 10};
  set<int> B = {1, 2, 4, 3, 4, 5, 5, 6, 7, 8, 9, 1, 10};
  ASSERT_EQ(A.size(), B.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    EXPECT_EQ(*it_1, *it_2);
  }
}

TEST(test_expect, set_decrements_iterator) {
  Set<int> A = {1, 2, 4, 3, 4, 5, 5, 6, 7, 8, 9, 1, 10};
  set<int> B = {1, 2, 4, 3, 4, 5, 5, 6, 7, 8, 9, 1, 10};
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

TEST(test_assert, set_emplace) {
  Set<std::string> x = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  auto vt = x.emplace("A", "B", "C");
  ASSERT_TRUE(7 == x.size());
}

TEST(test_assert, set_find) {
  Set<std::string> x = {"D", "H", "K", "J", "B"};
  set<std::string> x_1 = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  auto it = x.find("B");
  auto it_1 = x_1.find("B");
  ASSERT_EQ(*it, "B");
  ASSERT_EQ(*it, *it_1);
}

TEST(test_assert, set_contains) {
  Set<std::string> x = {"A", "D", "H", "K", "J", "B", "B", "D", "D", "D"};
  ASSERT_EQ(1, x.contains("B"));
  ASSERT_EQ(1, x.contains("D"));
  ASSERT_EQ(1, x.contains("A"));
  ASSERT_EQ(0, x.contains("I"));
}
