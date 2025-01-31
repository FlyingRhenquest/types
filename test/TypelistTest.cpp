/*
 * Copyright 2024 Bruce Ide
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <gtest/gtest.h>
#include <fr/types/Typelist.h>
#include <string>
#include <tuple>
#include <vector>

using namespace fr::types;

TEST(TypelistTests, IsTypelistTest) {
  ASSERT_FALSE(is_typelist<int>::value);
  using List = Typelist<int, char, bool>;
  ASSERT_TRUE(is_typelist<List>::value);
}

TEST(TypelistTests, ToTest) {
  using List = Typelist<int, char, bool>;
  auto listTuple = List::to<std::tuple>();
}

TEST(TypelistTests, Contains) {
  using list = Typelist<int, char, bool>;
  ASSERT_TRUE(list::contains<int>());
  ASSERT_TRUE(list::contains<char>());
  ASSERT_TRUE(list::contains<bool>());
  ASSERT_FALSE(list::contains<long>());
}

TEST(TypelistTests, IsUnique) {
  using uniqueList = Typelist<int, char, bool>;
  using nonUniqueList = Typelist<long, int, char, int, bool, char, int>;
  ASSERT_TRUE(uniqueList::is_unique());
  ASSERT_FALSE(nonUniqueList::is_unique());
}

TEST(TypelistTests, PushFrontAndBack) {
  using list = Typelist<int>;
  using frontList = list::push_front<bool>;
  using backList = list::push_back<char>;

  ASSERT_TRUE(frontList::contains<bool>());
  ASSERT_TRUE(backList::contains<char>());

  constexpr bool frontPos = std::is_same<bool, frontList::head::type>::value;
  constexpr bool backPos = std::is_same<char, backList::tail::head::type>::value;

  // Verify bool is in the correct location
  ASSERT_TRUE(frontPos);
  // Verify char is in the correct location
  ASSERT_TRUE(backPos);
}

TEST(TypelistTests, MergeTest) {
  using foo = Typelist<char, int>;
  using bar = Typelist<bool, long>;
  using merged = foo::merge<bar>;
  // using invalidMerge = foo::merge<int>; // Results in compile error due to concept violation (int is not a typelist)
  ASSERT_TRUE(merged::contains<char>());
  ASSERT_TRUE(merged::contains<int>());
  ASSERT_TRUE(merged::contains<bool>());
  ASSERT_TRUE(merged::contains<long>());
}

TEST(TypelistTests, MapTest) {
  using List = Typelist<char, int>;
  using VecList = List::template map<std::vector>;
  ASSERT_TRUE(VecList::contains<std::vector<char>>());
  ASSERT_TRUE(VecList::contains<std::vector<int>>());
  ASSERT_FALSE(VecList::contains<std::vector<std::string>>());
  
}
