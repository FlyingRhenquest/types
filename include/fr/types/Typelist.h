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
 * A typelist and supporting functions for compile time code
 * validation and generation.
 */

#pragma once

#include <type_traits>
#include <tuple>

namespace fr::types {

  template <typename... Types>
  class Typelist;
  
  // Test to see if a parameter is a typelist
  template <typename>
  struct is_typelist {
    static constexpr bool value = false;
  };

  // Test to see if a parameter is a typelist 
  template <typename... Types>
  struct is_typelist<Typelist<Types...>> {
    static constexpr bool value = true;
  };

  template<typename... T>
  concept IsTypelist = is_typelist<T...>::value;

  /**
   * A typelist. This embodies a list of types. You can create an
   * arbitrary typelist with "using" in order to use it. This Typelist
   * provides many helpers to add and remove types from the list,
   * check to see if the list has a specific type in it and that
   * sort of thing.
   *
   * Note that this is entirely composed of compile time constructs.
   * Specifically, none of this *exists* at run time. So if you want
   * an intersection of doing run time things with a typelist, it
   * can be helpful to create actual objects that you can work with.
   * You can can use Typelist::to in order to convert the typelist
   * into a tuple, which you can then iterate through using std::for_each.
   * This can be handy for creating event handlers, simulating switch
   * statements and all manner of other goodies. These operations will
   * be quite safe as the compiler is doing a lot of checking to
   * verify that the types you're working with are in your list.
   *
   * Request for Comment: I'm considering adding iteration through
   * the typelist in a for_each fashion but am not convinced that
   * it would be helpful versus creating a tuple of empty objects
   * to iterate through. If anyone has a solid use case, I'd like
   * to hear about it. I'd need some solid requirements around how
   * it should work.
   */
  
  template <typename... Types>
  class Typelist {
  public:
    using type = Typelist<Types...>;

    // RecursionHelper gives us a place to put constexpr functions
    // we want to use to be able to recurse through the list of types.
    // This is effectively implementing a compile time linked list
    // that we can iterate through.

    // This is the RecursionHelper end point. When this is returned,
    // there are no more types in the list.
    template <typename... Tail>
    struct RecursionHelper {
      using type = void;
      using tail = Typelist<void>;

      template <template<typename...> typename MapType>
      using map = Typelist<std::tuple<>>;

      template <typename Search>
      constexpr static bool contains() {
	return false;
      }

      constexpr static bool is_unique() {
	return true;
      }
    };
    
    // This is the RecursionHelper your typelist returns when
    // there are more objects in the Typelist.
    template <typename T, typename... Tail>
    struct RecursionHelper<T, Tail...> {
      using type = T;
      using tail = Typelist<Tail...>;

      // Map another templated type to a new typelist
      template <template<typename ...> typename MapType>
      using map = Typelist<MapType<type>>::template merge<typename tail::template map<MapType>>;

      template <typename Search>
      constexpr static bool contains() {
	if constexpr(std::is_same_v<Search, type>) {
	  return true;
	}
	return tail::template contains<Search>();
      }

      // Iterates over every element in the list and verfies each one is
      // unique
      constexpr static bool is_unique() {
	if constexpr(tail::template contains<type>()) {
	  return false;
	}
	return tail::is_unique();
      }
    };

    // MergeHelper allows us to merge two typelists.
    // Note that this does not check for unique types.
    // At some point I can add functionality for unique
    // lists, but at the moment the user must attend to
    // that if they need their lists to be unique.
    template <typename... ToMerge>
    requires IsTypelist<ToMerge...>
    struct MergeHelper {
      // use push_front or push_back for individual types
    };

    template <typename... MergeList>
    struct MergeHelper<Typelist<MergeList...>> {
      using merged = Typelist<Types..., MergeList...>;
    };

    template <typename MergeTypelist>
    using merge = MergeHelper<MergeTypelist>::merged;

    // Easy entry into RecursionHelper
    using head = RecursionHelper<Types...>;
    using tail = RecursionHelper<Types...>::tail;

    // Enables mapping this typelist to multiple templated
    // objects that specialize to the elemnts in this list
    template <template<typename ...> typename MapType>
    using map = head::template map<MapType>;

    // Test to see if this Typelist contains only unique types
    constexpr static bool is_unique() {
      return RecursionHelper<Types...>::is_unique();
    }

    // Test to see if this Typelist contains a specific type
    template <typename T>
    constexpr static bool contains() {
      return RecursionHelper<Types...>::template contains<T>();
    }
    
    // Convert the typelist to any type that accepts a
    // varadic parameter list. tuple is a good example.
    // Creating a tuple from a typelist WILL cause all
    // tuple elements to be instantiated with their type.
    // This doesn't necessarily mean they have to be default
    // constructable, but all the types in the list should
    // take the same constructor parameters.
    template <template<typename ...> typename ToType>
    using to = ToType<Types...>;

    // Append a type to this typelist
    template<typename T>
    using push_back = Typelist<Types..., T>;

    // Insert a type at the front of the list
    template<typename T>
    using push_front = Typelist<T, Types...>;

  };
  
}
