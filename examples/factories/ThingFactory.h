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
 * A factory class that creates a thing. You subscribe to the factory
 * via a boost signal. This makes it easy to shovel data into factories
 * in threads, although if you do that you may need to mutex protect your
 * handlers if you can receive more than one piece of data at a time.
 *
 * Note that the boost signals2 signal handler runs in the thread of
 * the caller of that signal, so you want to process data expeditiously
 * so as not to block whatever is going on in that thread.
 *
 * Thing must be trivially constructable.
 */

#pragma once
#include <boost/signals2.hpp>
#include <functional>
#include <type_traits>

template <typename T>
requires std::is_trivially_constructible<T>::value
class ThingFactory
{
 public:

  // Callback to signal data available
  boost::signals2::signal<void(const T&)> available;
  
  ThingFactory() {}
  ~ThingFactory() {}

  // Creates a default thing. You can do a create with a parameter
  // and pass that parameter to the T constructor as well. If T does
  // not have a constructor that takes a parameter of that type, you'll
  // get a compie time error.
  //
  // This does not return an object, it sends it out via a signal.
  // You have to assume that anything can subscribe to that signal
  // so you can't just assume you can move the object in a signal
  // handler, unless you constrain your application to prevent multiple
  // subscribers. One way to do that is to make the signal private and
  // keep a count in the subscribe function.
  
  void create() { available(T()); }

  // Convenience function to subscribe to available
  boost::signals2::connection subscribe(std::function<void(const T&)> subscriber) {
    return available.connect(subscriber);
  }
  
};
