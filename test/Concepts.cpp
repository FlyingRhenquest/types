/**
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
 *
 * Tests for concepts in Concepts.h
 */

#include <gtest/gtest.h>
#include <fr/types/Concepts.h>
#include <string>

using namespace fr::types;

// This returns a tuple from a typelist, for the purpose of
// testing the concept.
template<typename T>
constexpr auto toTuple() requires IsUnique<T> {
  return typename T::template to<std::tuple>();
}

// This returns a object of one type if that type is contained
// in a list, for the purpose of testing the concept
//
// Should probably also throw a is_default_constructable or something
// in here.
template<typename V, typename T>
constexpr auto makeIfContained() -> V // Shall return a V
  requires Contains<V, T> { // If it's contained in the list
  return V();
}

TEST(ConceptsTests, isUniqueTest) {
  using uniqueList = Typelist<std::string, char, int, bool, double>;
  using nonUnique = Typelist<std::string, int, bool, int, std::string, double, float, double>;
  auto typeTuple = toTuple<uniqueList>();
  // Next line will result in a compile error due to concept violation
  // auto badTuple = toTuple<nonUnique>();
}

TEST(ConceptTests, containsTest) {
  using List = Typelist<std::string, char, int, bool>;
  auto intThing = makeIfContained<int, List>();
  auto stringThing = makeIfContained<std::string, List>();
  // Next line will result in a compile error due to concept violation
  // auto badThing = makeIfContained<double, List>();
}
