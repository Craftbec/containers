#include <gtest/gtest.h>

#include <list>

#include "../s21_list.h"

using namespace std;
using namespace s21;

TEST(test_assert, list_constructor_std) {
  List<int> A;
  list<int> B;
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, list_constructor_size) {
  List<int> A(15);
  list<int> B(15);
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, list_constructor_variable) {
  List<int> A = {1, 2, 3, 4, 5, 6};
  list<int> B = {1, 2, 3, 4, 5, 6};
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, list_constructor_copy) {
  List<int> A_1 = {1, 2, 3};
  List<int> A(A_1);
  list<int> B_1 = {1, 2, 3};
  list<int> B(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, list_constructor_move) {
  List<int> A_1 = {1, 2, 3};
  List<int> A(move(A_1));
  list<int> B_1 = {1, 2, 3};
  list<int> B(move(B_1));
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, list_operator_move) {
  List<int> A_1 = {1, 2, 3};
  List<int> A = move(A_1);
  list<int> B_1 = {1, 2, 3};
  list<int> B = move(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, list_methods_empty) {
  List<int> A;
  List<int> A_1 = {1, 2, 3};
  list<int> B;
  list<int> B_1 = {1, 2, 3};
  ASSERT_EQ(B.empty(), A.empty());
  ASSERT_EQ(B_1.empty(), A_1.empty());
}

TEST(test_assert, list_methods_size) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> A_1 = {1, 2, 3};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  list<int> B_1 = {1, 2, 3};
  ASSERT_FALSE(B.size() == A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
}

TEST(test_assert, methods_max_size_1) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(B.max_size(), A.max_size());
}

TEST(test_assert, methods_max_size_2) {
  List<std::string> A = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  list<std::string> B = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  ASSERT_EQ(B.max_size(), A.max_size());
}

TEST(test_assert, list_methods_clear) {
  List<int> A = {1, 2, 3};
  list<int> B = {1, 2, 3};
  A.clear();
  B.clear();
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, list_methods_insert_1) {
  List<int> A = {1, 2, 3};
  list<int> B = {1, 2, 3};
  auto it_1 = A.end();
  A.insert(it_1, 4);
  it_1 = A.begin();
  A.insert(it_1, 0);
  auto it_2 = B.end();
  B.insert(it_2, 4);
  it_2 = B.begin();
  B.insert(it_2, 0);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_insert_2) {
  List<int> A = {1, 2, 3};
  list<int> B = {1, 2, 3};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ++it_2;
  ++it_1;
  A.insert(it_1, 0);
  B.insert(it_2, 0);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_insert_3) {
  List<int> A = {1, 2, 3};
  list<int> B = {1, 2, 3};
  auto it_1 = A.end();
  auto it_2 = B.end();
  --it_2;
  --it_1;
  A.insert(it_1, 0);
  B.insert(it_2, 0);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_erase_1) {
  List<int> A = {0, 1, 2, 3, 4};
  list<int> B = {0, 1, 2, 3, 4};
  auto it_1 = A.begin();
  ++it_1;
  A.erase(it_1);
  auto it_2 = B.begin();
  ++it_2;
  B.erase(it_2);
  it_1 = A.begin();
  it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_erase_2) {
  List<int> A = {155};
  list<int> B = {155};
  ASSERT_EQ(B.size(), A.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  A.erase(it_1);
  B.erase(it_2);
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, list_methods_erase_3) {
  List<int> A = {0, 1, 2, 3, 4};
  list<int> B = {0, 1, 2, 3, 4};
  ASSERT_EQ(B.size(), A.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  A.erase(it_1);
  B.erase(it_2);
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, list_methods_erase_4) {
  List<int> A = {0, 1, 2, 3, 4};
  list<int> B = {0, 1, 2, 3, 4};
  ASSERT_EQ(B.size(), A.size());
  auto it_1 = A.end();
  auto it_2 = B.end();
  --it_1;
  --it_2;
  A.erase(it_1);
  B.erase(it_2);
  ASSERT_EQ(B.size(), A.size());
}

TEST(test_assert, list_methods_push_back) {
  List<int> A;
  list<int> B;
  for (int i = 0; i < 11; ++i) {
    A.push_back(i);
    B.push_back(i);
  }
  A.push_back(7);
  B.push_back(7);
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_push_front) {
  List<int> A;
  list<int> B;
  for (int i = 0; i < 11; ++i) {
    A.push_front(i);
    B.push_front(i);
  }
  A.push_front(7);
  B.push_front(7);
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_pop_back) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (; A.size();) {
    A.pop_back();
    B.pop_back();
    ASSERT_EQ(B.size(), A.size());
    auto it_1 = A.begin();
    auto it_2 = B.begin();
    for (int i = A.size(); i; --i) {
      ASSERT_EQ(*it_1, *it_2);
    }
  }
}

TEST(test_assert, list_methods_pop_front) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (; A.size();) {
    A.pop_front();
    B.pop_front();
    ASSERT_EQ(B.size(), A.size());
    auto it_1 = A.begin();
    auto it_2 = B.begin();
    for (int i = A.size(); i; --i) {
      ASSERT_EQ(*it_1, *it_2);
    }
  }
}

TEST(test_assert, list_methods_swap) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> A_1 = {11, 12, 13, 14, 15};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B_1 = {11, 12, 13, 14, 15};
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

TEST(test_assert, list_methods_merge_1) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> A_1 = {11, 12, 13, 14, 15};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B_1 = {11, 12, 13, 14, 15};
  A.merge(A_1);
  B.merge(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_merge_2) {
  List<int> A;
  List<int> A_1 = {11, 12, 13, 14, 15};
  list<int> B;
  list<int> B_1 = {11, 12, 13, 14, 15};
  A.merge(A_1);
  B.merge(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_merge_3) {
  List<int> A = {11, 12, 13, 14, 15};
  List<int> A_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B = {11, 12, 13, 14, 15};
  list<int> B_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  A.merge(A_1);
  B.merge(B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_splice_1) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> A_1 = {11, 12, 13, 14, 15};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B_1 = {11, 12, 13, 14, 15};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ++it_1;
  ++it_2;
  A.splice(it_1, A_1);
  B.splice(it_2, B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
  it_1 = A.begin();
  it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
  it_1 = A_1.begin();
  it_2 = B_1.begin();
  for (; it_1 != A_1.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_splice_2) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> A_1 = {11, 12, 13, 14, 15};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B_1 = {11, 12, 13, 14, 15};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  A.splice(it_1, A_1);
  B.splice(it_2, B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
  it_1 = A.begin();
  it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
  it_1 = A_1.begin();
  it_2 = B_1.begin();
  for (; it_1 != A_1.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_splice_3) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> A_1 = {11, 12, 13, 14, 15};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B_1 = {11, 12, 13, 14, 15};
  auto it_1 = A.end();
  auto it_2 = B.end();
  A.splice(it_1, A_1);
  B.splice(it_2, B_1);
  ASSERT_EQ(B.size(), A.size());
  ASSERT_EQ(B_1.size(), A_1.size());
  it_1 = A.begin();
  it_2 = B.begin();
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
  it_1 = A_1.begin();
  it_2 = B_1.begin();
  for (; it_1 != A_1.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_reverse) {
  List<int> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  list<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  A.reverse();
  B.reverse();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_unique) {
  List<int> A = {10, 10, 10, 1, 0, 2, 3,  4,  2,  5,
                 6,  7,  8,  8, 8, 9, 10, 11, 11, 11};
  list<int> B = {10, 10, 10, 1, 0, 2, 3,  4,  2,  5,
                 6,  7,  8,  8, 8, 9, 10, 11, 11, 11};
  A.unique();
  B.unique();
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_assert, list_methods_sort) {
  List<int> A = {10, 1, 0, 2, 3, 4, 2, 5, 6, 7, 8, 8, 9, 10};
  list<int> B = {10, 1, 0, 2, 3, 4, 2, 5, 6, 7, 8, 8, 9, 10};
  A.sort();
  B.sort();
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ASSERT_EQ(B.size(), A.size());
  for (; it_1 != A.end(); ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }
}

TEST(test_expect, list_increments_iterator) {
  List<int> A = {11, 22, 33, 44};
  list<int> B = {11, 22, 33, 44};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  ASSERT_EQ(*++it_2, *++it_1);
  ASSERT_EQ(*it_2++, 22);
  ASSERT_EQ(*it_1++, 22);
  ASSERT_EQ(*it_2, 33);
  ASSERT_EQ(*it_1, 33);
  ASSERT_EQ(*++it_2, 44);
  ASSERT_EQ(*++it_1, 44);
}

TEST(test_expect, list_decrements_iterator_1) {
  List<int> A = {11, 22, 33, 44};
  list<int> B = {11, 22, 33, 44};
  auto it_1 = A.end();
  auto it_2 = B.end();
  EXPECT_EQ(*--it_2, *--it_1);
  EXPECT_EQ(*it_2--, 44);
  EXPECT_EQ(*it_1--, 44);
  EXPECT_EQ(*it_2, 33);
  EXPECT_EQ(*it_1, 33);
  EXPECT_EQ(*--it_2, 22);
  EXPECT_EQ(*--it_1, 22);
}

TEST(test_expect, list_decrements_iterator_2) {
  List<int> A = {11, 22, 33, 44};
  list<int> B = {11, 22, 33, 44};
  auto it_1 = A.begin();
  auto it_2 = B.begin();
  --it_2;
  --it_1;
  --it_2;
  --it_1;
  EXPECT_EQ(*it_2--, 44);
  EXPECT_EQ(*it_1--, 44);
  EXPECT_EQ(*it_2, 33);
  EXPECT_EQ(*it_1, 33);
  EXPECT_EQ(*--it_2, 22);
  EXPECT_EQ(*--it_1, 22);
}

TEST(test_assert, list_emplace) {
  s21::List<std::string> x = {"D", "H", "K", "J", "B"};
  ASSERT_EQ(5, x.size());
  auto it = x.begin();
  it = x.emplace(it, "100", "-100", "-200");
  ASSERT_TRUE(8 == x.size());
}

TEST(test_assert, list_emplace_back) {
  List<std::string> x = {"D", "H", "K", "J", "E"};
  ASSERT_EQ(5, x.size());
  x.emplace_back("100", "-100", "-200");
  ASSERT_EQ(8, x.size());
  ASSERT_EQ("-200", *--x.end());
}

TEST(test_assert, list_emplace_front) {
  s21::List<std::string> x = {"D", "H", "K", "J", "E"};
  ASSERT_EQ(5, x.size());
  x.emplace_front("C", "B", "A");
  ASSERT_EQ(8, x.size());
  ASSERT_EQ("A", *x.begin());
}
