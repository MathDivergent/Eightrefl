#ifndef EIGHTREFL_STANDARD_STACK_HPP
#define EIGHTREFL_STANDARD_STACK_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <stack> // stack

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// default container for stack
#include <Eightrefl/Standard/deque.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, class ContainerType>),
    (std::stack<ValueType, ContainerType>), std::stack<eightrefl::clean_of<ValueType>, eightrefl::clean_of<ContainerType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::stack<ValueType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::stack<" + eightrefl::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType, class ContainerType>), std::stack<ValueType, ContainerType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::stack<" + eightrefl::name_of<ValueType>() + ", " + eightrefl::name_of<ContainerType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType, class ContainerType>), std::stack<ValueType, ContainerType>)
    FACTORY(R())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(typename R::container_type const&))
    #endif // EIGHTREFL_FULLY_ENABLE

    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(top, typename R::reference())
    FUNCTION(top, typename R::const_reference() const)
    FUNCTION(empty)
    FUNCTION(size)
    FUNCTION(push, void(typename R::const_reference))
    FUNCTION(pop)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_STACK_HPP
