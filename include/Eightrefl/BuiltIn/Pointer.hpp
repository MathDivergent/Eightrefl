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


TEMPLATE_REFLECTABLE_DECLARATION((template <typename ElementType, std::size_t SizeValue>), ElementType(*)[SizeValue])
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME("std::type_identity_t<" + eightrefl::name_of<ElementType[SizeValue]>() + ">*")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()


#ifdef EIGHTREFL_MEMBER_ENABLE
TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ReflectableType, typename PropertyType>),
    PropertyType ReflectableType::*,
    eightrefl::clean_of<PropertyType> ReflectableType::*
)

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReflectableType, typename PropertyType>),
    PropertyType ReflectableType::*
)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME(eightrefl::name_of<PropertyType>() + " " + eightrefl::name_of<ReflectableType>() + "::*")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ReflectableType, typename PropertyType>), PropertyType ReflectableType::*)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReflectableType, typename ElementType, std::size_t SizeValue>),
    ElementType(ReflectableType::*)[SizeValue]
)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME("std::type_identity_t<" + eightrefl::name_of<ElementType[SizeValue]>() + "> " + eightrefl::name_of<ReflectableType>() + "::*")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()
#endif // EIGHTREFL_MEMBER_ENABLE

#endif // EIGHTREFL_BUILTIN_POINTER_HPP
