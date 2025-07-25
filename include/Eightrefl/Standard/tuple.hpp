#ifndef EIGHTREFL_STANDARD_TUPLE_HPP
#define EIGHTREFL_STANDARD_TUPLE_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <tuple> // tuple

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename... ArgumentTypes>),
    (std::tuple<ArgumentTypes...>), std::tuple<eightrefl::clean_of<ArgumentTypes>...>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <>, std::tuple<>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::tuple<>")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ArgumentType, typename... ArgumentTypes>),
    std::tuple<ArgumentType, ArgumentTypes...>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::tuple<" + ( eightrefl::name_of<ArgumentType>() + ... + (", " + eightrefl::name_of<ArgumentTypes>()) ) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename... ArgumentTypes>), std::tuple<ArgumentTypes...>)
    FACTORY(R())
    FACTORY(R(ArgumentTypes...))
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_TUPLE_HPP
