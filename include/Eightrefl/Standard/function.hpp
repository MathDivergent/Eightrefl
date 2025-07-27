#ifndef EIGHTREFL_STANDARD_FUNCTION_HPP
#define EIGHTREFL_STANDARD_FUNCTION_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <functional> // function

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#ifdef EIGHTREFL_FULLY_ENABLE
// as function return type
#include <Eightrefl/Standard/typeinfo.hpp>
#endif // EIGHTREFL_FULLY_ENABLE

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    (std::function<ReturnType(ArgumentTypes...)>), std::function<eightrefl::clean_of<ReturnType(ArgumentTypes...)>>
)

REFLECTABLE_DECLARATION(std::function<void()>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    std::function<ReturnType(ArgumentTypes...)>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::function<" + eightrefl::name_of<ReturnType(ArgumentTypes...)>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ReturnType, typename... ArgumentTypes>),
    std::function<ReturnType(ArgumentTypes...)>
)
    FACTORY(R())
    FACTORY(R(std::nullptr_t))
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator=, R&(std::nullptr_t))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator bool)
    FUNCTION(operator())

    #ifdef EIGHTREFL_FULLY_ENABLE
    #ifdef EIGHTREFL_RTTI_ENABLE
    FUNCTION(target_type)
    #endif // EIGHTREFL_RTTI_ENABLE
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_FUNCTION_HPP
