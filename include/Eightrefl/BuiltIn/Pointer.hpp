#ifndef EIGHTREFL_BUILTIN_POINTER_HPP
#define EIGHTREFL_BUILTIN_POINTER_HPP

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/BuiltIn.hpp>

TEMPLATE_REFLECTABLE_CLEAN(template <typename ElementType>, ElementType*, eightrefl::clean_of<ElementType>*)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ElementType>, ElementType*)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME(eightrefl::name_of<ElementType>() + "*")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ElementType>, ElementType*)
    META("*", eightrefl::find_or_add_type<ElementType>())
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

#endif // EIGHTREFL_BUILTIN_POINTER_HPP
