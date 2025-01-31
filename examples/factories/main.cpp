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
 */

#include <random>

#include "AggregateFactory.h"
#include "ThingBuffer.h"
#include "TrivialObjects.h"
#include <fr/types/Typelist.h>

int main(int argc, char *argv[]) {
  std::cout << "Thing Factory Example" << std::endl;
  std::cout << "Setting up factories and storage..." << std::endl;
  using TrivialObjects = fr::types::Typelist<Foo, Bar, Baz>;
  AggregateFactory<TrivialObjects> factories;
  ThingBuffer<TrivialObjects> buffers;
  buffers.subscribeTo(factories);
  std::cout << "Creating objects..." << std::endl;
  std::random_device r;
  std::mt19937 rng(r());
  std::uniform_int_distribution<std::mt19937::result_type> getRandom(1,3);
  for (int i = 0; i < 30; ++i) {
    switch(getRandom(rng)) {
    case 1:
      std::cout << "Creating a Foo" << std::endl;
      factories.get<Foo>().create();
      break;
    case 2:
      std::cout << "Creating a Bar" << std::endl;
      factories.get<Bar>().create();
      break;
    case 3:
      std::cout << "Creating a Baz" << std::endl;
      factories.get<Baz>().create();
      break;
    }
  }

  std::cout << std::endl << "Buffer status: " << std::endl;
  buffers.bufferStatus();
}
