---
title: Compile-time computation
category: cpp
layout: main
---

The goal of these exercises is to get some feeling about the possibilities
offered by the C++ language to perform computations at compile-time.

## Exercise 1

Take the `pi` function in
[`pi_time.cpp`]({{site.exercises_repo}}/hands-on/basic/pi_time.cpp) and make it
`constexpr`

Look at the assembly (the easiest is to copy&paste the code into the [Compiler
Explorer](https://godbolt.org/)) and verify that there is no computation
performed at runtime.

## Exercise 2

Implement a `constexpr` function that checks if a number is prime.

Like before, look at the assembly and verify that there is no computation
performed at runtime for a _statically_ known value.

Check that it's possible to call the function with a non-statically know value,
e.g. one that is asked on the standard input.

## Exercise 3

Take
[`containers_assoc.cpp`]({{site.exercises_repo}}/hands-on/cpp/containers_assoc.cpp)
and extend it to cover also the use of the `std::set` and `std::unordered_set`
associative containers. To fill the associative containers you can simply insert
all the numbers from 0 to N, without random generation and without advancing.

In
order to dispatch to the correct implementation you can use the `is_associative`
trait already included in that file, using it either as a tag or in a
_constexpr-if_.

## Exercise 4

Construct a compile-time table corresponding to a [Pascal’s
Triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle) of N rows, where N
is a compile-time constant.

Look at the assembly and verify that there is no computation performed at
runtime for a statically known value of a certain position, but that it's also
possible to access the value for a position obtained at runtime, e.g. from
standard input.
