#ifndef EIGHTREFL_STANDARD_REFERENCE_WRAPPER_HPP
#define EIGHTREFL_STANDARD_REFERENCE_WRAPPER_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <functional> // reference_wrapper

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ValueType>,
    std::reference_wrapper<ValueType>, std::reference_wrapper<eightrefl::clean_of<ValueType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::reference_wrapper<ValueType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::reference_wrapper<" + eightrefl::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ValueType>, std::reference_wrapper<ValueType>)
    FACTORY(R(ValueType&))
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    NAMED_FUNCTION(("operator " + eightrefl::name_of<ValueType&>()), operator eightrefl::clean_of<ValueType>&)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(get)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_REFERENCE_WRAPPER_HPP
