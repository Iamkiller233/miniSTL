// Copyright 2020 Yu Kainan

#include "abc/list.h"

#include <algorithm>
#include <chrono>
#include <list>

#include "abc/data/copyable.h"
#include "gtest/gtest.h"

class TestList : public ::testing::Test {
 protected:
  // helper class
  using Kitten = abc::data::Copyable;
  // common data
  std::list<int> std_list_of_id{ 4, 3, 2, 1 };
  std::list<Kitten> std_list_of_kitten;
  abc::list<Kitten> abc_list_of_kitten;
};

TEST_F(TestList, Empty) {
  EXPECT_EQ(abc_list_of_kitten.empty(), std_list_of_kitten.empty());
}

TEST_F(TestList, Size) {
  for (int i = 0; i < 10; i++) abc_list_of_kitten.emplace_back(-1);
  EXPECT_EQ(abc_list_of_kitten.size(), 10);
}

TEST_F(TestList, EmpalceFront) {
  for (auto i : std_list_of_id) {
    std_list_of_kitten.emplace_front(i);
    abc_list_of_kitten.emplace_front(i);
  }
  EXPECT_EQ(abc_list_of_kitten.empty(), std_list_of_kitten.empty());
}
TEST_F(TestList, Front) {
  for (auto i : std_list_of_id) {
    std_list_of_kitten.emplace_front(i);
    abc_list_of_kitten.emplace_front(i);
  }
  EXPECT_EQ(abc_list_of_kitten.front(), std_list_of_kitten.front());
}
TEST_F(TestList, EmpalceBack) {
  for (auto i : std_list_of_id) {
    std_list_of_kitten.emplace_back(i);
    abc_list_of_kitten.emplace_back(i);
  }
  EXPECT_EQ(abc_list_of_kitten.empty(), std_list_of_kitten.empty());
}
TEST_F(TestList, Back) {
  for (auto i : std_list_of_id) {
    std_list_of_kitten.emplace_back(i);
    abc_list_of_kitten.emplace_back(i);
  }
  EXPECT_EQ(abc_list_of_kitten.back(), std_list_of_kitten.back());
}

TEST_F(TestList, PopFront) {
  for (auto i : std_list_of_id) {
    std_list_of_kitten.emplace_front(i);
    abc_list_of_kitten.emplace_front(i);
  }
  while (!std_list_of_kitten.empty()) {
    std_list_of_kitten.pop_front();
    abc_list_of_kitten.pop_front();
    EXPECT_EQ(abc_list_of_kitten.empty(), std_list_of_kitten.empty());
  }
}

TEST_F(TestList, PopBack) {
  for (auto i : std_list_of_id) {
    std_list_of_kitten.emplace_back(i);
    abc_list_of_kitten.emplace_back(i);
  }
  while (!std_list_of_kitten.empty()) {
    std_list_of_kitten.pop_back();
    abc_list_of_kitten.pop_back();
    EXPECT_EQ(abc_list_of_kitten.empty(), std_list_of_kitten.empty());
  }
}

TEST_F(TestList, Iterator) {
  for (auto i : std_list_of_id) {
    abc_list_of_kitten.emplace_front(i);
  }
  auto iter = std::find(abc_list_of_kitten.begin(),
    abc_list_of_kitten.end(), Kitten(2));
  EXPECT_NE(iter, abc_list_of_kitten.end());
  EXPECT_EQ(*iter, Kitten(2));

  auto iter1 = std::find(abc_list_of_kitten.begin(),
    abc_list_of_kitten.end(), Kitten(-2));
  EXPECT_EQ(iter1, abc_list_of_kitten.end());
}

TEST_F(TestList, Erase) {
  for (auto i : std_list_of_id) {
    abc_list_of_kitten.emplace_front(i);
    std_list_of_kitten.emplace_front(i);
  }
  auto iter_abc = abc_list_of_kitten.begin();
  iter_abc++;
  auto iter_std = std_list_of_kitten.begin();
  iter_std++;
  iter_abc = abc_list_of_kitten.erase(iter_abc);
  iter_std = std_list_of_kitten.erase(iter_std);

  EXPECT_EQ(*iter_std, *iter_abc);
  while (!std_list_of_kitten.empty()) {
    EXPECT_EQ(abc_list_of_kitten.front(), std_list_of_kitten.front());
    std_list_of_kitten.pop_front();
    abc_list_of_kitten.pop_front();
  }
}

TEST_F(TestList, Emplace) {
  for (auto i : std_list_of_id) {
    abc_list_of_kitten.emplace_back(i);
    std_list_of_kitten.emplace_back(i);
  }
  auto ykn_iter = std::find(abc_list_of_kitten.begin(),
                              abc_list_of_kitten.end(), Kitten(2));
  ykn_iter = abc_list_of_kitten.emplace(ykn_iter, 0);
  auto std_iter = std::find(std_list_of_kitten.begin(),
                              std_list_of_kitten.end(), Kitten(2));
  std_iter = std_list_of_kitten.emplace(std_iter, 0);
  EXPECT_EQ(*std_iter, *ykn_iter);
  while (!std_list_of_kitten.empty()) {
    EXPECT_EQ(abc_list_of_kitten.back(), std_list_of_kitten.back());
    std_list_of_kitten.pop_back();
    abc_list_of_kitten.pop_back();
  }
}

TEST_F(TestList, Equal) {
  auto new_list_of_kitten = decltype(abc_list_of_kitten)();
  for (auto i : std_list_of_kitten) {
    abc_list_of_kitten.emplace_front(i);
    new_list_of_kitten.emplace_front(i);
  }
  EXPECT_TRUE(abc_list_of_kitten == abc_list_of_kitten);
  EXPECT_TRUE(abc_list_of_kitten == new_list_of_kitten);
  EXPECT_FALSE(abc_list_of_kitten != abc_list_of_kitten);
  EXPECT_FALSE(abc_list_of_kitten != new_list_of_kitten);
}
TEST_F(TestList, Copy) {
  for (auto i : std_list_of_kitten) {
    abc_list_of_kitten.emplace_front(i);
  }
  auto new_list_of_kitten = abc_list_of_kitten;
  EXPECT_EQ(new_list_of_kitten, abc_list_of_kitten);
  new_list_of_kitten = abc_list_of_kitten;
  EXPECT_EQ(new_list_of_kitten, abc_list_of_kitten);
  new_list_of_kitten = new_list_of_kitten;
  EXPECT_EQ(new_list_of_kitten, abc_list_of_kitten);
}
TEST_F(TestList, Move) {
  for (auto i : std_list_of_kitten) {
    abc_list_of_kitten.emplace_front(i);
  }
  auto copy_list_of_kitten = abc_list_of_kitten;
  auto move_list_of_kitten = abc::move(abc_list_of_kitten);
  EXPECT_EQ(move_list_of_kitten, copy_list_of_kitten);

  abc_list_of_kitten = abc::move(copy_list_of_kitten);
  EXPECT_EQ(abc_list_of_kitten, copy_list_of_kitten);

  move_list_of_kitten = abc::move(move_list_of_kitten);
  EXPECT_EQ(move_list_of_kitten, abc_list_of_kitten);
}

TEST_F(TestList, Performance) {
  using clock = std::chrono::high_resolution_clock;
  int n = 1000000;
  auto ticks = [n](auto& list) {
    auto start = clock::now();
    for (int i = 0; i != n; i++) {
      list.emplace_back(i);
    }
    list.clear();
    std::chrono::duration<double> duration = clock::now()-start;
    return duration.count();
  };
  auto t_std = ticks(std_list_of_kitten);
  auto t_ykn = ticks(abc_list_of_kitten);
  EXPECT_LT(t_ykn/t_std, 1.2);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
