#ifndef EIGHTREFL_STANDARD_TYPE_INDEX_HPP
#define EIGHTREFL_STANDARD_TYPE_INDEX_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#ifdef EIGHTREFL_RTTI_ENABLE
#include <typeindex> // type_index

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/Standard/Standard.hpp>

REFLECTABLE_DECLARATION(std::type_index)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()
#endif // EIGHTREFL_RTTI_ENABLE
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_TYPE_INDEX_HPP
