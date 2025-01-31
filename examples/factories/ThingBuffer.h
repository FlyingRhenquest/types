/**
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
 * Provides a buffer for trivial objects. It's scarcely worth making
 * an object for except that it wants a couple of functions to show
 * you what's going on inside it.
 *
 * Since this is designed to hold trivial objects, it assumes that
 * every object type stored in it has a to_s method.
 */

#pragma once

#include <boost/signals2.hpp>
#include <iostream>
#include <string>
#include <fr/types/AggregateType.h>
#include <vector>

// All types in the list must be unique
// Trivial objects are stored in std::vector when they're created

// If the factory remains active after this object goes out of scope
// you will certainly crash. To avoid this, store the connections
// returned by AggregateFactory::subscribe and unsubscribe them
// in the destructor of this object.

template <typename List>
requires fr::types::IsTypelist<List> && fr::types::IsUnique<List>
class ThingBuffer : public fr::types::AggregateType<std::vector, List> {
public:

  using Parent = fr::types::AggregateType<std::vector, List>;
  
  // Subscribe all buffers in this list to its related factory
  // in a AggregateFactory

  template <typename FactoryType,
	    typename ObjectList = List>
  void subscribeTo(FactoryType& factories) {
    using ElementType = typename ObjectList::head::type;
    using NextElementType = typename ObjectList::tail::head::type;
    // Retrieve a reference to the vector for the current type,
    // which is stored in the AggregateType we derive from
    auto& vectorRef = Parent::template get<ElementType>();
    factories.template subscribe<ElementType>([&](const auto& trivialThing) {
      // We're making a copy because there can be other subscribers
      // to the object. Otherwise we could use std::move here.
      vectorRef.push_back(trivialThing);
    });

    if constexpr(!std::is_void_v<NextElementType>) {
      subscribeTo<FactoryType, typename ObjectList::tail>(factories);
    }
  }

  template<typename ObjectList = List>
  void bufferStatus() {
    using ElementType = typename ObjectList::head::type;
    using NextElementType = typename ObjectList::tail::head::type;
    std::cout << ElementType::to_s() << " buffer size... " << Parent::template get<ElementType>().size() << std::endl;
    if constexpr (!std::is_void_v<NextElementType>) {
      bufferStatus<typename ObjectList::tail>();
    }
  }
  
};
