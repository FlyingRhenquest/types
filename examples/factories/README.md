# Factories Example

Requires boost::signals2

Typelists and related constructs are compile-time, which constrains
what you can do with them at run time. This is a solid feature if you
want to catch as many errors as possible at compile time, but it
is inconvienent if you want your program behavior to change based on
user interactions.

This example illustrates how to randomly create, store and print some
trivial objects using the compile-time constructs. It basically works
out to some sort of switch statement being pretty much unavoidable at
some point, but if you're clever about it you can make the compiler
generate that code for you.
