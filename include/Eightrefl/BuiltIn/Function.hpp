#ifndef EIGHTREFL_BUILTIN_FUNCTION_HPP
#define EIGHTREFL_BUILTIN_FUNCTION_HPP

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/BuiltIn.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    (ReturnType(ArgumentTypes...)), eightrefl::clean_of<ReturnType>(eightrefl::clean_of<ArgumentTypes>...)
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ReturnType>, ReturnType())
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME(eightrefl::name_of<ReturnType>() + "()")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReturnType, typename ArgumentType, typename... ArgumentTypes>),
    ReturnType(ArgumentType, ArgumentTypes...)
)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME(eightrefl::name_of<ReturnType>() + "(" + ( eightrefl::name_of<ArgumentType>() + ... + (", " + eightrefl::name_of<ArgumentTypes>()) ) + ")")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    (ReturnType(ArgumentTypes...)&), eightrefl::clean_of<ReturnType(ArgumentTypes...)>&
)

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    ReturnType(ArgumentTypes...)&
)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME(eightrefl::name_of<ReturnType(ArgumentTypes...)>() + "&")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    (ReturnType(ArgumentTypes...) const), eightrefl::clean_of<ReturnType(ArgumentTypes...)> const
)

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    ReturnType(ArgumentTypes...) const
)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME(eightrefl::name_of<ReturnType(ArgumentTypes...)>() + " const")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    (ReturnType(ArgumentTypes...) const&), eightrefl::clean_of<ReturnType(ArgumentTypes...)> const&
)

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    ReturnType(ArgumentTypes...) const&
)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME(eightrefl::name_of<ReturnType(ArgumentTypes...)>() + " const&")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    ReturnType(*)(ArgumentTypes...)
)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME("std::type_identity_t<" + eightrefl::name_of<ReturnType(ArgumentTypes...)>() + ">*")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    ReturnType(*)(ArgumentTypes...)
)
REFLECTABLE_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReturnType, typename ReflectableType, typename... ArgumentTypes>),
    ReturnType(ReflectableType::*)(ArgumentTypes...)
)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME("std::type_identity_t<" + eightrefl::name_of<ReturnType(ArgumentTypes...)>() + "> " + eightrefl::name_of<ReflectableType>() + "::*")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ReturnType, typename ReflectableType, typename... ArgumentTypes>),
    ReturnType(ReflectableType::*)(ArgumentTypes...)
)
REFLECTABLE_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    ReturnType(&)(ArgumentTypes...)
)
    REFLECTABLE_REGISTRY(eightrefl::builtin())
    REFLECTABLE_NAME("std::type_identity_t<" + eightrefl::name_of<ReturnType(ArgumentTypes...)>() + ">&")
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

#endif // EIGHTREFL_BUILTIN_FUNCTION_HPP
