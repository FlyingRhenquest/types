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
 */

#include "associations.h"
#include <fr/types/Typelist.h>
#include <iostream>

// Print the name of the type of the head of the list and
// recurse if there are any more types
template<typename List>
constexpr void printHead(int i)
  requires fr::types::IsTypelist<List> {
  std::cout << i << "... " << fr::associations::Types<typename List::head::type>::name << std::endl;
  if constexpr (!std::is_void_v<typename List::tail::head::type>) {
    printHead<typename List::tail>(++i);
  }
}

int main(int argc, char* argv[]) {
  std::cout << "Looking up int type: " << fr::associations::Types<int>::name << std::endl;
  std::cout << "Lookng up float type (should be notfound): " << fr::associations::Types<float>::name << std::endl;
  // This is determined at compile time, so the generated check should
  // not have anything other than a "True" or a "False" at run time,
  // And it will never change unless you recompile.
  std::cout << "Float type Types::type is void: " << (std::is_void_v<fr::associations::Types<float>::type> ? "True" : "False") << std::endl;
  // Lets do a typelist
  using DemoTypes = fr::types::Typelist<bool, float, char*, int, std::string, long, double>;

  std::cout << "Types in DemoTypes (Should be Bool, notfound, notfound, Int, String, notfound, notfound):" << std::endl;
  printHead<DemoTypes>(1);
  
  std::cout << std::endl;
  
}
