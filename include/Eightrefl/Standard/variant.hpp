#ifndef EIGHTREFL_STANDARD_VARIANT_HPP
#define EIGHTREFL_STANDARD_VARIANT_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <variant> // variant, monostate

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

REFLECTABLE_DECLARATION(std::monostate)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()


TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ArgumentType, typename... ArgumentTypes>),
    (std::variant<ArgumentType, ArgumentTypes...>), std::variant<eightrefl::clean_of<ArgumentType>, eightrefl::clean_of<ArgumentTypes>...>
)

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ArgumentType, typename... ArgumentTypes>),
    std::variant<ArgumentType, ArgumentTypes...>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::variant<" + ( eightrefl::name_of<ArgumentType>() + ... + (", " + eightrefl::name_of<ArgumentTypes>()) ) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ArgumentType, typename... ArgumentTypes>),
    std::variant<ArgumentType, ArgumentTypes...>
)
    FACTORY(R())
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(index)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(valueless_by_exception)
    FUNCTION(swap, void(R&))
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_VARIANT_HPP
