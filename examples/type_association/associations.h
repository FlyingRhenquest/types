/*
 * Copyright 2025 Bruce Ide
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
 * This header creates an index named Types which just contains the name
 * of the type it is associated with. While I'm manually laying them out
 * in this case, this sort of index really lends itself well to code
 * generation.
 */

#pragma once

#include <string>

namespace fr::associations {

  // This structure is the "not found" case.
  template <typename T>
  struct Types {
    // You can check the Type to make sure it matches
    // the one you're looking for if you need to worry
    // about that.
    using type = void; 
    // This is pointing at a const string in const space.
    // You can't actually write to these strings after they've
    // been defined. Since each templated type is a different type,
    // this can be static. These indexes can also contain static
    // constexpr functions that can be different based on
    // specialized type.
    static constexpr char name[] = "NOTFOUND";
  };

  // Specialize on types you want in the index

  template <>
  struct Types<std::string> {
    using type = std::string;
    static constexpr char name[] = "String";
  };

  template <>
  struct Types<int> {
    using type = int;
    static constexpr char name[] = "Int";
  };

  template <>
  struct Types<bool> {
    using type = bool;
    static constexpr char name[] = "Bool";
  };

}
