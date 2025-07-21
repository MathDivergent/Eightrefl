#ifndef EIGHTREFL_BUILTIN_STATIC_ARRAY_HPP
#define EIGHTREFL_BUILTIN_STATIC_ARRAY_HPP

#include <cstddef> // size_t

#include <string> // to_string

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/BuiltIn.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ElementType, std::size_t SizeValue>),
    ElementType[SizeValue], eightrefl::clean_of<ElementType>[SizeValue]
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ElementType, std::size_t SizeValue>), ElementType[SizeValue])
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME(eightrefl::name_of<ElementType>() + "[" + std::to_string(SizeValue) + "]")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ElementType, std::size_t SizeValue>), ElementType(*)[SizeValue])
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME("std::type_identity_t<" + eightrefl::name_of<ElementType[SizeValue]>() + ">*")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ElementType, std::size_t SizeValue>), ElementType(&)[SizeValue])
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME("std::type_identity_t<" + eightrefl::name_of<ElementType[SizeValue]>() + ">&")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

#endif // EIGHTREFL_BUILTIN_STATIC_ARRAY_HPP