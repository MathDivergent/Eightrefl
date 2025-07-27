#ifndef EIGHTREFL_BUILTIN_VOID_HPP
#define EIGHTREFL_BUILTIN_VOID_HPP

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/BuiltIn.hpp>

REFLECTABLE_DECLARATION(void)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

#endif // EIGHTREFL_BUILTIN_VOID_HPP
