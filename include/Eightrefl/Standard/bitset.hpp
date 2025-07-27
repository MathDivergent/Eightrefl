#ifndef EIGHTREFL_STANDARD_BITSET_HPP
#define EIGHTREFL_STANDARD_BITSET_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <string> // to_string

#include <bitset> // bitest

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// as function argument tye
#include <Eightrefl/Standard/string.hpp>

#include <Eightrefl/Standard/Standard.hpp>

#ifdef EIGHTREFL_FULLY_ENABLE
TEMPLATE_REFLECTABLE_USING
(
    template <class StdBitsetType>, std_bitset_reference,
    std_bitset_reference<StdBitsetType>, typename eightrefl::clean_of<StdBitsetType>::reference
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdBitsetType>, std_bitset_reference<StdBitsetType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME(eightrefl::name_of<StdBitsetType>() + "::reference")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdBitsetType>, std_bitset_reference<StdBitsetType>)
    FUNCTION(operator=, R&(bool))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator=, R&(R const&))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator bool)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator~)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(flip, R&())
REFLECTABLE_INIT()
#endif // EIGHTREFL_FULLY_ENABLE

TEMPLATE_REFLECTABLE_DECLARATION(template <std::size_t SizeValue>, std::bitset<SizeValue>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::bitset<" + std::to_string(SizeValue) + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <std::size_t SizeValue>, std::bitset<SizeValue>)
    FACTORY(R())
    FACTORY(R(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(unsigned long))
    #endif // EIGHTREFL_FULLY_ENABLE

    FACTORY(R(unsigned long long))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(std::string const&, std_size_t))
    #endif // EIGHTREFL_FULLY_ENABLE

    FACTORY(R(std::string const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(char const*, std_size_t))
    FACTORY(R(char const*))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator==)

    #ifdef EIGHTREFL_FULLY_ENABLE
//  FUNCTION(operator[], bool(std_size_t) const)
//  FUNCTION(operator[], std_bitset_reference<R>(std_size_t))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(test)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(all)
    FUNCTION(any)
    FUNCTION(none)
    FUNCTION(count)
    FUNCTION(size)
    FUNCTION(operator&=)
    FUNCTION(operator|=)
    FUNCTION(operator^=)
    FUNCTION(operator~)
    FUNCTION(operator<<)
    FUNCTION(operator<<=)
    FUNCTION(operator>>)
    FUNCTION(operator>>=)
    FUNCTION(set, R&())
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(set, R&(std_size_t, bool))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(reset, R&())
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(reset, R&(std_size_t))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(flip, R&())
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(flip, R&(std_size_t))
    FUNCTION(to_string, std::string(char, char) const)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(to_ulong)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(to_ullong)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_BITSET_HPP
