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
 *
 * Generic type that can be aggregated with a Typelist
 */

#pragma once

#include <fr/types/Typelist.h>
#include <fr/types/Concepts.h>
#include <tuple>

namespace fr::types {

  /**
   * This object creates a tuple of "Type" types, each
   * each element of which is specialized by the type
   * in the list.
   *
   * For example, using a Typelist<char, int> and a "Type"
   * type of vector, the tuple will contain a vector<char>
   * and a vector<int>. For reasons, the typelist for this
   * aggregate object must contain unique types (no type
   * should be contained more than once.)
   *
   * This class is moderately useful on its own but is designed
   * to be specialized.
   */
  
  template <template<typename...> typename Type,
	    typename List>
  requires IsTypelist<List> && IsUnique<List>
  class AggregateType {
  public:
    // Original Typelist
    using ListType = List;
    // List of vector of Types
    using MapTypes = List::template map<Type>;
    // Tuple of vector of types
    using TupleType = MapTypes::template to<std::tuple>;

    // Retrieve a specific vector of a specific type
    // contained in the list. Since we're not passing
    // an object type, you need to specify get<type>()
    //
    // You want to use the original unmodified type
    // and will retrieve a Type<type>& of the type
    // you pass it. So if you say get<int>(), you
    // will retrieve a reference to a contained vector
    // of it.
    //
    // If the original list did not contain the type
    // you requested, you will get a compiler error

    template <typename Retr>
    constexpr auto& get() requires (List::template contains<Retr>()) {
      return std::get<Type<Retr>>(_storage);
    }
    
  protected:

    // The actual Tuples of vectors of types
    TupleType _storage;
  };
  
}
