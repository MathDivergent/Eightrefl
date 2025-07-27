#ifndef EIGHTREFL_BUILTIN_QUALIFIER_HPP
#define EIGHTREFL_BUILTIN_QUALIFIER_HPP

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/BuiltIn.hpp>

TEMPLATE_REFLECTABLE_CLEAN(template <typename ElementType>, ElementType&, eightrefl::clean_of<ElementType>&)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ElementType>, ElementType&)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    BUILTIN_REFLECTABLE()
    REFLECTABLE_NAME(eightrefl::name_of<ElementType>() + "&")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_CLEAN(template <typename ElementType>, ElementType const, eightrefl::clean_of<ElementType> const)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ElementType>, ElementType const)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME(eightrefl::name_of<ElementType>() + " const")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

#endif // EIGHTREFL_BUILTIN_QUALIFIER_HPP