#ifndef EIGHTREFL_STANDARD_ARRAY_HPP
#define EIGHTREFL_STANDARD_ARRAY_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <array> // array
#include <string> // to_string

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#ifdef EIGHTREFL_FULLY_ENABLE
// as function argument type
#include <Eightrefl/Standard/iterator.hpp>
#endif // EIGHTREFL_FULLY_ENABLE_DISABLE

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, std::size_t SizeValue>),
    (std::array<ValueType, SizeValue>), std::array<eightrefl::clean_of<ValueType>, SizeValue>
)

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType, std::size_t SizeValue>), std::array<ValueType, SizeValue>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::array<" + eightrefl::name_of<ValueType>() + ", " + std::to_string(SizeValue) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType, std::size_t SizeValue>), std::array<ValueType, SizeValue>)
    FACTORY(R())
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(at, typename R::const_reference(typename R::size_type) const)
    FUNCTION(at, typename R::reference(typename R::size_type))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator[], typename R::const_reference(typename R::size_type) const)
    FUNCTION(operator[], typename R::reference(typename R::size_type))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(front, typename R::reference())
    FUNCTION(back, typename R::const_reference() const)
    FUNCTION(back, typename R::reference())
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(data, typename R::const_pointer() const)
    FUNCTION(data, typename R::pointer())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_iterator<R>())
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(end, std_iterator<R>())
    FUNCTION(cend, std_const_iterator<R>() const)
    FUNCTION(rbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(rbegin, std_reverse_iterator<R>())
    FUNCTION(crbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(rend, std_const_reverse_iterator<R>() const)
    FUNCTION(rend, std_reverse_iterator<R>())
    FUNCTION(crend, std_const_reverse_iterator<R>() const)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(empty)
    FUNCTION(size)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(max_size)
    FUNCTION(fill)
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_ARRAY_HPP
