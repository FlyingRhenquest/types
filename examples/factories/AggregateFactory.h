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
 * Provides an Aggregate Factory class that extends the ThingFactory
 * class and provides a subscribe helper function that redirects
 * the subscription request to the factory for a specific type.
 *
 */

#pragma once

#include <boost/signals2.hpp>
#include <fr/types/AggregateType.h>
#include <functional>
#include <type_traits>
#include "ThingFactory.h"

// You can only have one of each factory type in the list

template <typename List>
requires fr::types::IsTypelist<List> && fr::types::IsUnique<List>
class AggregateFactory : public fr::types::AggregateType<ThingFactory, List> {
public:

  using Parent = fr::types::AggregateType<ThingFactory, List>;
  
  template <typename FactoryObject>
  boost::signals2::connection subscribe(std::function<void(const FactoryObject&)> subscriber) {
    // Gets a ThingFactory of Factory object (AggregateType does this)
    // Subscribes your callback function to that ThingFactory
    // Returns the boost connection if you want to track the subscription.

    return Parent::template get<FactoryObject>().subscribe(subscriber);
  }
};
