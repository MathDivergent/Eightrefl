#ifndef EIGHTREFL_BUILTIN_ALIASING_HPP
#define EIGHTREFL_BUILTIN_ALIASING_HPP

#include <cstddef> // size_t, ptrdiff_t

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/BuiltIn.hpp>

REFLECTABLE_USING(std_size_t, std::size_t)

REFLECTABLE_DECLARATION(std_size_t)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME("std::size_t")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()


REFLECTABLE_USING(std_ptrdiff_t, std::ptrdiff_t)

REFLECTABLE_DECLARATION(std_ptrdiff_t)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME("std::ptrdiff_t")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

#endif // EIGHTREFL_BUILTIN_ALIASING_HPP
