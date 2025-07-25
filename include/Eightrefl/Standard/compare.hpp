#ifndef EIGHTREFL_STANDARD_COMPARE_HPP
#define EIGHTREFL_STANDARD_COMPARE_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#if __cplusplus > 201703L
#include <compare> // strong_ordering

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/Standard/Standard.hpp>

REFLECTABLE_DECLARATION(std::partial_ordering)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(std::weak_ordering)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(std::strong_ordering)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()
#endif // if
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_COMPARE_HPP
