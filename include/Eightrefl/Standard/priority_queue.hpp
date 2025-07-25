#ifndef EIGHTREFL_STANDARD_PRIORITY_QUEUE_HPP
#define EIGHTREFL_STANDARD_PRIORITY_QUEUE_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <queue> // priority_queue

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// default container for priority_queue
#include <Eightrefl/Standard/vector.hpp>

// less - default comparator for priority_queue
#include <Eightrefl/Standard/functional.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, class ContainerType, class ComparatorType>),
    (std::priority_queue<ValueType, ContainerType, ComparatorType>),
    std::priority_queue<eightrefl::clean_of<ValueType>, eightrefl::clean_of<ContainerType>, eightrefl::clean_of<ComparatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::priority_queue<ValueType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::priority_queue<" + eightrefl::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType, class ContainerType>), std::priority_queue<ValueType, ContainerType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::priority_queue<" + eightrefl::name_of<ValueType>() + ", " + eightrefl::name_of<ContainerType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ValueType, class ContainerType, class ComparatorType>),
    std::priority_queue<ValueType, ContainerType, ComparatorType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::priority_queue<" + eightrefl::name_of<ValueType>() + ", " + eightrefl::name_of<ContainerType>() + ", "
                                            + eightrefl::name_of<ComparatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ValueType, class ContainerType, class ComparatorType>),
    std::priority_queue<ValueType, ContainerType, ComparatorType>
)
    FACTORY(R())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(typename R::value_compare const&, typename R::container_type const&))
    FACTORY(R(typename R::value_compare const&))
    #endif // EIGHTREFL_FULLY_ENABLE

    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
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

#endif // EIGHTREFL_STANDARD_PRIORITY_QUEUE_HPP
