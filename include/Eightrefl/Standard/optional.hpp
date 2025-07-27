#ifndef EIGHTREFL_STANDARD_OPTIONAL_HPP
#define EIGHTREFL_STANDARD_OPTIONAL_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <optional> // optional, nullopt_t

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

REFLECTABLE_DECLARATION(std::nullopt_t)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()


TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ValueType>,
    std::optional<ValueType>, std::optional<eightrefl::clean_of<ValueType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::optional<ValueType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::optional<" + eightrefl::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ValueType>, std::optional<ValueType>)
    FACTORY(R())
    FACTORY(R(std::nullopt_t))
    FACTORY(R(R const&))
    FACTORY(R(typename R::value_type const&))
    FUNCTION(operator=, R&(std::nullopt_t))
    FUNCTION(operator=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator->, typename R::value_type const*() const)
    FUNCTION(operator->, typename R::value_type*())
    FUNCTION(operator*, typename R::value_type const&() const&)
    FUNCTION(operator*, typename R::value_type&()&)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator bool)

    #ifdef EIGHTREFL_FULLY_ENABLE
//  FUNCTION(has_value)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(value, typename R::value_type&()&)
    FUNCTION(value, typename R::value_type const&() const&)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(value_or, typename R::value_type(typename R::value_type const&) const&)
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE

//  FUNCTION(reset)
    FUNCTION(emplace, typename R::value_type&(typename R::value_type const&))
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_OPTIONAL_HPP
