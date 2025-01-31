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
 * Tests for AggregateTypes
 */

#include <gtest/gtest.h>
#include <fr/types/AggregateType.h>
#include <string>
#include <vector>

using namespace fr::types;

TEST(AggregateType, vectorTest) {
  // Let's make an aggregate object of vectors of types
  // and put some stuff in those vectors
  using List = Typelist<std::string, int, bool>;
  using ListAggregate = AggregateType<std::vector,List>;

  ListAggregate aggregate;

  aggregate.get<std::string>().push_back("Hello world!");
  aggregate.get<bool>().push_back(true);
  ASSERT_EQ(aggregate.get<std::string>().size(), 1);
  ASSERT_EQ(aggregate.get<int>().size(), 0);
  ASSERT_EQ(aggregate.get<bool>().size(), 1);
  // Next line results in a compile time constraint violation
  // because our aggregate type does not contain a vector of double.
  // auto& Vec = aggregate.get<double>();
}
