#ifndef EIGHTREFL_BUILTIN_NULLPTR_HPP
#define EIGHTREFL_BUILTIN_NULLPTR_HPP

#include <cstddef> // nullptr_t

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/BuiltIn.hpp>

REFLECTABLE_DECLARATION(std::nullptr_t)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

#endif // EIGHTREFL_BUILTIN_NULLPTR_HPP
