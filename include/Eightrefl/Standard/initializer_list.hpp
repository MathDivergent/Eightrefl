#ifndef EIGHTREFL_STANDARD_INITIALIZER_LIST_HPP
#define EIGHTREFL_STANDARD_INITIALIZER_LIST_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <initializer_list> // initializer_list

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ValueType>,
    std::initializer_list<ValueType>, std::initializer_list<eightrefl::clean_of<ValueType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::initializer_list<ValueType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::initializer_list<" + eightrefl::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ValueType>, std::initializer_list<ValueType>)
    FACTORY(R())
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    
    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(begin)
    FUNCTION(end)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(size)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_INITIALIZER_LIST_HPP
