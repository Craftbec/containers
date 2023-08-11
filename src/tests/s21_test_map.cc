#include <gtest/gtest.h>

#include <map>

#include "../s21_map.h"

using namespace std;
using namespace s21;

TEST(test_assert, map_constructor_default) {
  Map<int, std::string> x;
  map<int, std::string> y;
  ASSERT_EQ(y.size(), x.size());
}

TEST(test_assert, map_constructor_variable) {
  Map<int, std::string> x = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                             {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> y = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                             {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                             {-4, "- FOUR"}};
  ASSERT_EQ(y.size(), x.size());
  ASSERT_EQ(y.at(0), x.at(0));
}

TEST(test_assert, map_constructor_copy) {
  Map<int, std::string> x = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                             {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                               {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                               {-4, "- FOUR"}};
  Map<int, std::string> y(x);
  map<int, std::string> y_1(x_1);

  ASSERT_EQ(y.size(), y_1.size());
  ASSERT_EQ(x.size(), x_1.size());
  ASSERT_EQ(y.at(-3), y_1.at(-3));
  ASSERT_EQ(x.at(-3), x_1.at(-3));
}

TEST(test_assert, map_constructor_move) {
  Map<int, std::string> x = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                             {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                               {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                               {-4, "- FOUR"}};
  Map<int, std::string> y(std::move(x));
  map<int, std::string> y_1(std::move(x_1));
  ASSERT_EQ(0, x.size());
  ASSERT_EQ(x.size(), x_1.size());
  ASSERT_EQ(7, y.size());
  ASSERT_EQ(y_1.size(), y.size());
}

TEST(test_assert, map_operator_move_1) {
  Map<int, std::string> x = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                             {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                               {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                               {-4, "- FOUR"}};
  Map<int, std::string> y = std::move(x);
  map<int, std::string> y_1 = std::move(x_1);
  ASSERT_EQ(0, x.size());
  ASSERT_EQ(x.size(), x_1.size());
  ASSERT_EQ(7, y.size());
  ASSERT_EQ(y_1.size(), y.size());
}

TEST(test_assert, map_operator_move_2) {
  Map<int, std::string> x = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                             {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                               {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                               {-4, "- FOUR"}};
  Map<int, std::string> y;
  map<int, std::string> y_1;
  y = std::move(x);
  y_1 = std::move(x_1);
  ASSERT_EQ(0, x.size());
  ASSERT_EQ(x.size(), x_1.size());
  ASSERT_EQ(7, y.size());
  ASSERT_EQ(y_1.size(), y.size());
}

TEST(test_assert, map_operator_copy_1) {
  Map<int, std::string> x = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                             {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                               {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                               {-4, "- FOUR"}};
  Map<int, std::string> y = x;
  map<int, std::string> y_1 = x_1;
  ASSERT_EQ(7, x.size());
  ASSERT_EQ(x.size(), x_1.size());
  ASSERT_EQ(7, y.size());
  ASSERT_EQ(y_1.size(), y.size());
  ASSERT_EQ(y.at(-3), x.at(-3));
  ASSERT_EQ(y_1.at(-3), x_1.at(-3));
}

TEST(test_assert, map_operator_copy_2) {
  Map<int, std::string> x = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                             {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},    {2, "TWO"},       {3, "THREE"},
                               {0, "ZERO"},   {-3, "-- THREE"}, {4, "FOUR"},
                               {-4, "- FOUR"}};
  Map<int, std::string> y;
  map<int, std::string> y_1;
  y = x;
  y_1 = x_1;
  ASSERT_EQ(7, x.size());
  ASSERT_EQ(x.size(), x_1.size());
  ASSERT_EQ(7, y.size());
  ASSERT_EQ(y_1.size(), y.size());
  ASSERT_EQ(y.at(-3), x.at(-3));
  ASSERT_EQ(y_1.at(-3), x_1.at(-3));
}

TEST(test_assert, map_at_method) {
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                               {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                               {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  ASSERT_EQ(x_1.at(0), x.at(0));
  ASSERT_EQ(x_1.at(-4), x.at(-4));
  ASSERT_EQ(x_1.at(1), x.at(1));
}

TEST(test_assert, map_operator_square_brackets) {
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                               {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                               {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  x[44] = "FOURTYFOUR";
  x_1[44] = "FOURTYFOUR";
  ASSERT_EQ(x_1.at(44), x.at(44));
  ASSERT_EQ(x_1.size(), x.size());
  x_1[44] = "FOURTYFOUR";
  x[44] = "FOURTYFOUR";
  ASSERT_EQ(8, x.size());
  ASSERT_EQ(8, x_1.size());
}

TEST(test_assert, map_begin_iterator) {
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                               {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                               {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  auto it_1 = x.begin();
  auto it_2 = x_1.begin();
  ASSERT_EQ(x.size(), x_1.size());
  for (; it_1 != x.end(); ++it_1, ++it_2) {
    ASSERT_EQ((*it_1).first, (*it_2).first);
    ASSERT_EQ((*it_1).second, (*it_2).second);
  }
}

TEST(test_assert, map_begin_iterator_1) {
  Map<int, std::string> x;
  map<int, std::string> x_1;
  x.begin();
  x_1.begin();
}

TEST(test_assert, map_end_iterator_2) {
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                               {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                               {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  auto it_1 = x.end();
  auto it_2 = x_1.end();
  --it_1;
  --it_2;
  for (; it_1 != x.begin(); --it_1, --it_2) {
    ASSERT_EQ((*it_1).first, (*it_2).first);
    ASSERT_EQ((*it_1).second, (*it_2).second);
  }
  ASSERT_EQ((*it_1).first, (*it_2).first);
  ASSERT_EQ((*it_1).second, (*it_2).second);
}

TEST(test_assert, map_iterator_plusplus) {
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                               {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                               {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  auto it_1 = x.end();
  auto it_2 = x_1.end();
  --it_1;
  --it_2;
  for (; it_1 != x.begin(); --it_1, --it_2) {
    ASSERT_EQ((*it_1).first, (*it_2).first);
    ASSERT_EQ((*it_1).second, (*it_2).second);
  }
  ASSERT_EQ((*it_1).first, (*it_2).first);
  ASSERT_EQ((*it_1).second, (*it_2).second);
}

TEST(test_assert, map_iterator_minusminus_1) {
  Map<int, std::string> x = {{4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{4, "FOUR"}, {-4, "- FOUR"}};
  auto it_1 = x.begin();
  auto it_2 = x_1.begin();
  --it_1;
  --it_2;
  ++it_1;
  ++it_2;
  for (; it_1 != x.begin(); --it_1, --it_2) {
    ASSERT_EQ((*it_1).first, (*it_2).first);
    ASSERT_EQ((*it_1).second, (*it_2).second);
  }
  ASSERT_EQ((*it_1).first, (*it_2).first);
  ASSERT_EQ((*it_1).second, (*it_2).second);
}

TEST(test_assert, map_iterator_minusminus_2) {
  Map<int, std::string> x = {{-4, "- FOUR"}, {4, "FOUR"}};
  map<int, std::string> x_1 = {{-4, "- FOUR"}, {4, "FOUR"}};
  auto it_1 = x.begin();
  auto it_2 = x_1.begin();
  ASSERT_EQ((*it_1).first, (*it_2).first);
  ASSERT_EQ((*it_1).second, (*it_2).second);
  --it_1;
  --it_1;
}

TEST(test_assert, map_iterator_minusminus_3) {
  Map<int, std::string> x = {
      {0, "ZERO"}, {-4, "- FOUR"}, {-6, "- SIX"}, {4, "FOUR"}};
  map<int, std::string> x_1 = {
      {0, "ZERO"}, {-4, "- FOUR"}, {-6, "- SIX"}, {4, "FOUR"}};
  auto it_1 = x.begin();
  auto it_2 = x_1.begin();
  ASSERT_EQ((*it_1).first, (*it_2).first);
  ASSERT_EQ((*it_1).second, (*it_2).second);
  ++it_1;
  ++it_2;
  --it_1;
  --it_2;
  ASSERT_EQ((*it_1).first, (*it_2).first);
  ASSERT_EQ((*it_1).second, (*it_2).second);
}

TEST(test_assert, map_iterator_minusminus_4) {
  Map<int, std::string> x = {{0, "ZERO"},     {-4, "- FOUR"}, {-2, "- TWO"},
                             {-3, "- THREE"}, {-6, "- SIX"},  {4, "FOUR"}};
  map<int, std::string> x_1 = {{0, "ZERO"},     {-4, "- FOUR"}, {-2, "- TWO"},
                               {-3, "- THREE"}, {-6, "- SIX"},  {4, "FOUR"}};
  auto it_1 = x.begin();
  auto it_2 = x_1.begin();
  ASSERT_EQ((*it_1).first, (*it_2).first);
  ASSERT_EQ((*it_1).second, (*it_2).second);
  for (; it_1 != x.end(); ++it_1, ++it_2) {
    ASSERT_EQ((*it_1).first, (*it_2).first);
    ASSERT_EQ((*it_1).second, (*it_2).second);
  }
  --it_1;
  --it_2;
  for (; it_1 != x.begin(); --it_1, --it_2) {
    ASSERT_EQ((*it_1).first, (*it_2).first);
    ASSERT_EQ((*it_1).second, (*it_2).second);
  }
}

TEST(test_assert, map_empty_method) {
  Map<int, std::string> y;
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> y_1;
  map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                               {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                               {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  ASSERT_EQ(y_1.empty(), y.empty());
  ASSERT_EQ(x_1.empty(), x.empty());
}

// = This method (max_size) diffrent with oem container (it is norm) = //

// TEST(test_assert, map_max_size_method_1) {
//   Map<int, std::string> x;
//   map<int, std::string> y;
//   ASSERT_EQ(y.max_size(), x.max_size());
// }

// TEST(test_assert, map_max_size_method_2) {
//   Map<std::string, std::string> x;
//   map<std::string, std::string> y;
//   ASSERT_EQ(y.max_size(), x.max_size());
// }

TEST(test_assert, map_size_method) {
  Map<int, std::string> y;
  Map<int, std::string> y_1;
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                               {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                               {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  ASSERT_EQ(x_1.size(), x.size());
  ASSERT_EQ(y_1.size(), y.size());
}

TEST(test_assert, map_clear) {
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                               {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                               {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  x.clear();
  x_1.clear();
  ASSERT_EQ(x_1.size(), x.size());
  x[123] = "-=123=-";
  x_1[123] = "-=123=-";
  ASSERT_EQ(x_1.size(), x.size());
  ASSERT_EQ(x_1.at(123), x.at(123));
  x.clear();
  x_1.clear();
  ASSERT_EQ(x_1.size(), x.size());
}

TEST(test_assert, map_insert_1) {
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  Map<int, std::string>::value_type vt = std::make_pair(150, "-=150=-");
  map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                               {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                               {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string>::value_type vt_1 = std::make_pair(150, "-=150=-");
  x.insert(vt);
  x_1.insert(vt_1);
  ASSERT_EQ(x_1.at(150), x.at(150));
  ASSERT_EQ("-=150=-", x.at(150));
  x.insert(vt);
  x.insert(vt_1);
  ASSERT_EQ(x_1.at(150), x.at(150));
  ASSERT_EQ("-=150=-", x.at(150));
}

TEST(test_assert, map_insert_2) {
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  x.insert(150, "-=150=-");
  ASSERT_TRUE("-=150=-" == x.at(150));
}

TEST(test_assert, map_insert_or_assign) {
  Map<int, std::string> x = {{1, "ONE"},       {3, "THREE"}, {0, "ZERO"},
                             {-3, "-- THREE"}, {2, "TWO"},   {4, "FOUR"},
                             {-4, "- FOUR"}};
  ASSERT_TRUE("TWO" == x.at(2));
  x.insert_or_assign(2, "-=2=-");
  x.insert_or_assign(150, "-=150=-");
  ASSERT_TRUE("-=2=-" == x.at(2));
  ASSERT_TRUE("-=150=-" == x.at(150));
}

TEST(test_assert, map_erase_1) {
  Map<int, std::string> x = {{1, "ONE"},       {3, "THREE"}, {0, "ZERO"},
                             {-3, "-- THREE"}, {2, "TWO"},   {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},       {3, "THREE"}, {0, "ZERO"},
                               {-3, "-- THREE"}, {2, "TWO"},   {4, "FOUR"},
                               {-4, "- FOUR"}};
  auto it = x.begin();
  auto it_1 = x_1.begin();
  ASSERT_EQ((*it).first, (*it_1).first);
  ++it;
  ++it_1;
  x.erase(it);
  x_1.erase(it_1);
  it = x.begin();
  it_1 = x_1.begin();
  ++it;
  ++it_1;
  x.erase(it);
  x_1.erase(it_1);
  ASSERT_EQ(x.size(), x_1.size());
  it = x.begin();
  it_1 = x_1.begin();
  for (; it != x.end(); ++it, ++it_1) {
    ASSERT_EQ((*it).first, (*it_1).first);
  }
}

TEST(test_assert, map_erase_2) {
  Map<int, std::string> x = {{-4, "- FOUR"}};
  map<int, std::string> x_1 = {{-4, "- FOUR"}};
  auto it = x.begin();
  auto it_1 = x_1.begin();
  ASSERT_EQ((*it).first, (*it_1).first);
  x.erase(it);
  x_1.erase(it_1);
  ASSERT_EQ(x.size(), x_1.size());
}

TEST(test_assert, map_erase_3) {
  Map<int, std::string> x = {{-4, "- FOUR"}, {4, "FOUR"}};
  map<int, std::string> x_1 = {{-4, "- FOUR"}, {4, "FOUR"}};
  auto it = x.begin();
  auto it_1 = x_1.begin();
  ASSERT_EQ((*it).first, (*it_1).first);
  x.erase(it);
  x_1.erase(it_1);
  ASSERT_EQ(x.size(), x_1.size());
}

TEST(test_assert, map_erase_4) {
  Map<int, std::string> x = {{4, "FOUR"}, {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{4, "FOUR"}, {-4, "- FOUR"}};
  auto it = x.begin();
  auto it_1 = x_1.begin();
  ++it;
  ++it_1;
  ASSERT_EQ((*it).first, (*it_1).first);
  x.erase(it);
  x_1.erase(it_1);
  ASSERT_EQ(x.size(), x_1.size());
}

TEST(test_assert, map_erase_5) {
  Map<int, std::string> x = {
      {4, "FOUR"}, {-4, "- FOUR"}, {-2, "- TWO"}, {-1, "- ONE"}};
  map<int, std::string> x_1 = {
      {4, "FOUR"}, {-4, "- FOUR"}, {-2, "- TWO"}, {-1, "- ONE"}};
  auto it = x.begin();
  auto it_1 = x_1.begin();
  ++it_1;
  ++it;
  ASSERT_EQ((*it).first, (*it_1).first);
  x.erase(it);
  x_1.erase(it_1);
  ASSERT_EQ(x.size(), x_1.size());
}

TEST(test_assert, map_erase_6) {
  for (int i = 0; i < 17; ++i) {
    static int st = 0;
    Map<int, std::string> x = {
        {12, "12"}, {0, "0"},    {13, "13"}, {18, "18"},   {15, "15"},
        {24, "24"}, {14, "14"},  {17, "17"}, {16, "16"},   {20, "20"},
        {30, "30"}, {22, "22"},  {10, "10"}, {-10, "-10"}, {-5, "-5"},
        {8, "8"},   {-15, "-15"}};
    auto it = x.begin();
    for (int j = 0; j < st; ++j, ++it) {
    }
    x.erase(it);
    st++;
  }
}

TEST(test_assert, map_swap) {
  Map<int, std::string> x = {{1, "ONE"},       {3, "THREE"}, {0, "ZERO"},
                             {-3, "-- THREE"}, {2, "TWO"},   {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},       {3, "THREE"}, {0, "ZERO"},
                               {-3, "-- THREE"}, {2, "TWO"},   {4, "FOUR"},
                               {-4, "- FOUR"}};
  Map<int, std::string> y = {{14, "FOURTEEN"}, {-44, "-FOURTYFOUR"}};
  map<int, std::string> y_1 = {{14, "FOURTEEN"}, {-44, "-FOURTYFOUR"}};
  ASSERT_TRUE(x_1.size() == x.size());
  ASSERT_TRUE(y_1.size() == y.size());
  x.swap(y);
  x_1.swap(y_1);
  ASSERT_TRUE(x_1.size() == x.size());
  ASSERT_TRUE(y_1.size() == y.size());
  ASSERT_EQ(x_1.at(14), x.at(14));
  ASSERT_EQ(y_1.at(1), y.at(1));
}

TEST(test_assert, map_merge) {
  Map<int, std::string> x = {{1, "ONE"},       {3, "THREE"}, {0, "ZERO"},
                             {-3, "-- THREE"}, {2, "TWO"},   {4, "FOUR"},
                             {-4, "- FOUR"}};
  map<int, std::string> x_1 = {{1, "ONE"},       {3, "THREE"}, {0, "ZERO"},
                               {-3, "-- THREE"}, {2, "TWO"},   {4, "FOUR"},
                               {-4, "- FOUR"}};
  Map<int, std::string> y = {{14, "FOURTEEN"}, {-44, "-FOURTYFOUR"}};
  map<int, std::string> y_1 = {{14, "FOURTEEN"}, {-44, "-FOURTYFOUR"}};
  x.merge(y);
  ASSERT_TRUE("-FOURTYFOUR" == x.at(-44));
  ASSERT_TRUE("FOUR" == x.at(4));
}

TEST(test_assert, map_contains_method) {
  Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
                             {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
                             {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
  ASSERT_EQ(1, x.contains(0));
  ASSERT_EQ(0, x.contains(44));
}

TEST(test_assert, map_emplace) {
  s21::Map<int, std::string> x = {
      {12, "12"}, {0, "0"},     {13, "13"}, {18, "18"}, {15, "15"},  {24, "24"},
      {14, "14"}, {17, "17"},   {16, "16"}, {20, "20"}, {30, "30"},  {22, "22"},
      {10, "10"}, {-10, "-10"}, {-5, "-5"}, {8, "8"},   {-15, "-15"}};
  ASSERT_EQ(17, x.size());
  Vector<std::pair<Map<int, std::string>::iterator, bool>> vt =
      x.emplace(std::make_pair(100, "100"), std::make_pair(16, "16"),
                std::make_pair(-100, "-100"), std::make_pair(-200, "-200"));
  ASSERT_TRUE("100" == x.at(100));
  ASSERT_TRUE("-100" == x.at(-100));
  ASSERT_TRUE("-200" == x.at(-200));
  ASSERT_TRUE(20 == x.size());
  ASSERT_TRUE(vt[0].second == 1);
  ASSERT_TRUE(vt[1].second == 0);
  ASSERT_TRUE(vt[2].second == 1);
  ASSERT_TRUE(vt[3].second == 1);
}

// ============ Test's with throw exception (leak's) =============== //

// TEST(test_expect, map_at_method) {
//   Map<int, std::string> x = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
//                              {-3, "- THREE"}, {0, "ZERO"}, {-3, "-- THREE"},
//                              {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
//   map<int, std::string> x_1 = {{1, "ONE"},      {2, "TWO"},  {3, "THREE"},
//                                {-3, "- THREE"}, {0, "ZERO"}, {-3, "--THREE"},
//                                {2, "TWO"},      {4, "FOUR"}, {-4, "- FOUR"}};
//   EXPECT_ANY_THROW(x_1.at(11));
//   EXPECT_ANY_THROW(x.at(11));
// }
