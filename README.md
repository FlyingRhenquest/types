# Flying Rhenquest Types Library

This is a repo for me to noodle around with C++20 types and metaprogramming.

# What's here

## [Typelist](include/fr/types/Typelist.h)

[Typelist Unit Tests](test/TypelistTest.cpp).

Typelists allow you to store and manipulate a list of types as a template. This is a comple time construct that can be used to restrict types passed to a template or create aggregates of multiple similar looking objects that just need to exist somewhere. The list effectively does not exist at run time, so the interface between compile time and run time must be considered carefully when using them.

## [Concepts](include/fr/types/Concepts.h)

[Concepts unit tests](test/Concepts.cpp).

Some concepts to apply with Typelists. The Typelist header contains a concept to check to see if a templated parameter is a Typelist. This header lets you specify that the typelist is unique or that the typelist contains a specific type. This allows accurate compile time error reporting when one of those constraints has been violated.

## [AggregateType](include/fr/types/AggregateType)

[AggregateType Unit Tests](test/AggregateType.cpp).

Aggregate type allows you to create an aggregate tuple of multiple tempalated objects. The unit tests use std::vector as an example. It also provides a function to obtain a reference to a specific type by way of the object the vector contains.

For example, if you create an aggregate type with vector and have a string in the typelist, you can retrieve a reference to the stored string vector by specifying string as the type you want to retrieve.

If you're thinking you can use this instead of std::variant to store different types, it depends on your use case. If you require sequential access to all the objects inserted to the aggregate type as a whole, this does not provide this. Each vector exists independent of the other. You could potentially specialize AggregateType to include insert operations that preserve the overall order of insertions, but all methods of doing so are going to be problematic in one way or another.

## test

Unit test directory. This is a good place to look to see the basic usage
of these objects.

## examples

Small example programs.

### factories

The factory example demonstrates the use of the AggregateType class.
It subclasses AggregateType to create a factory for trivial objects
and another subclass to store them in a buffer (just std::vectors) as
they're created. The main.cpp creates a random group of objects,
stores them in their respective buffers and prints out the state
of the buffer at the end.

### type_association

Demonstrates how to associate strings with types using metaprogramming
and how to iterate through a typelist.

# Building

By default the build won't build anything but will install the library
as a header-only interface library.

To build tests and examples, use

```
cmake -DBUILD_TESTS=ON -DBUILD_EXAMPELS=ON
```

By default cmake will generally install in /usr/local. CMake
creates a find package which you can access in other CMake
instrumentation with:

```
find_package(FRTypes REQUIRED)
```

If you then add the project to your link libraries, that seems to
work (Which is as far as I'm ever willing to commit when CMake is
involved.)

```
target_link_libraries(mytarget PRIVATE FR::Types ...)
```
