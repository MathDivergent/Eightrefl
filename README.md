# Eightrefl - Simple reflection library 

![Type](https://img.shields.io/badge/type-engine%20module-%235a6770)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![Platforms](https://img.shields.io/badge/platforms-Windows%20%7C%20Linux%20%7C%20macOS-red)
![Tests](https://img.shields.io/badge/tests-automated-yellow)
[![License: MIT](https://img.shields.io/badge/license-MIT-green)](https://opensource.org/license/mit)

`Eightrefl` is a flexible and extensible C++ library with many features, that will allow you to easily reflects your code. The library has a small code base, but enough to use it. Is an external module of the [Eightgine](https://github.com/MathDivergent/Eightgine) (game engine).

Use macros for code generation or read the documentation and write your own code. 

A library implemented purely in C++17.

See last stable library version 2.7.1 [here](https://github.com/MathDivergent/Eightrefl/releases).

## Functional: 

### Reflection of common types:
- void
- std::nullptr_t
- bool
- char, wchar_t, char8_t (since C++20), char16_t, char32_t
- signed char, unsigned char, int, unsigned int, long, unsigned long, long long, unsigned long long, float, double, long double
- std::size_t, std::ptrdiff_t
- pointer, member pointer

### Reflection declaration (only) of special types:
- reference, const, const reference
- static array
- function 

See full list [here](https://github.com/MathDivergent/Eightrefl/tree/master/include/Eightrefl/BuiltIn). 

### Reflection of standard library types:
- C++11:
  - Containers: vector, array, basic_string, list, forward_list, set, unorganized_set, map, unordered_map, deque, initializer_list
  - Adapters: stack, queue, priority_queue
  - Smart pointers: unique_ptr, shared_ptr, weak_ptr
  - Other: pair, tuple, allocator, bitset, complex, reference_wrapper, char_traits
  - Functional: function, typeinfo, typeindex hash, equal_to, less, greater
  - Iterators: const_iterator, iterator, const_reverse_iterator, reverse_iterator, const_local_iterator, local_iterator
- C++17:
  - Functional: any, optional, variant
- C++20:
  - Compare: partial_ordering, weak_ordering, strong_ordering 

See full list [here](https://github.com/MathDivergent/Eightrefl/tree/master/include/Eightrefl/Standard). 

### Reflection of custom types:
- struct, class, union
- enum, scoped enum 

### Reflection of attributes:
- Parent
- Factory
- Function
- Property
- Bitfield
- Meta

### Library features:
- General:
  - [Reflectable injection](https://github.com/MathDivergent/Eightrefl/blob/master/test/TestInjection.cpp)
  - [Registry splitting](https://github.com/MathDivergent/Eightrefl/blob/master/src/Eightrefl/Standard/any.cpp)
  - [Reflectable using](https://github.com/MathDivergent/Eightrefl/blob/master/test/TestUsing.cpp)
- Builtin:
  - [Template reflection](https://github.com/MathDivergent/Eightrefl/blob/master/include/Eightrefl/Standard/stack.hpp)
  - [Conditional reflection](https://github.com/MathDivergent/Eightrefl/blob/master/include/Eightrefl/Standard/set.hpp)
  - [Reflectable naming](https://github.com/MathDivergent/Eightrefl/blob/master/include/Eightrefl/BuiltIn/Aliasing.hpp)
  - [Simple without macro](https://github.com/MathDivergent/Eightrefl/blob/master/test/TestWithoutMacro.cpp)
  - [Reflection meta](https://github.com/MathDivergent/Eightrefl/blob/master/test/TestMeta.cpp)
## Auto Tests:
See library testing [here](https://github.com/MathDivergent/Eightrefl/tree/master/test). 

## License:
This library is an open source project licensed under: [MIT](https://opensource.org/licenses/MIT).
