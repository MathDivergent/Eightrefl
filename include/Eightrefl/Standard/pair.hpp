#ifndef EIGHTREFL_STANDARD_PAIR_HPP
#define EIGHTREFL_STANDARD_PAIR_HPP

#include <utility> // pair

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename FirstType, typename SecondType>),
    (std::pair<FirstType, SecondType>), std::pair<eightrefl::clean_of<FirstType>, eightrefl::clean_of<SecondType>>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename FirstType, typename SecondType>), std::pair<FirstType, SecondType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::pair<" + eightrefl::name_of<FirstType>() + ", " + eightrefl::name_of<SecondType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename FirstType, typename SecondType>), std::pair<FirstType, SecondType>)
    FACTORY(R())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(typename R::first_type const&, typename R::second_type const&))
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(swap, void(R&))
    #endif // EIGHTREFL_FULLY_ENABLE

    PROPERTY(first, typename R::first_type)
    PROPERTY(second, typename R::second_type)
REFLECTABLE_INIT()

#endif // EIGHTREFL_STANDARD_PAIR_HPP
