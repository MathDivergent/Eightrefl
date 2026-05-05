#ifndef EIGHTREFL_DEV_DELETER_HPP
#define EIGHTREFL_DEV_DELETER_HPP

#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/ReflectableDeclaration.hpp>

#include <Eightrefl/Dev/Dev.hpp>

template <>
struct xxeightrefl_property_is_settable<std::unordered_map<std::string, eightrefl::deleter_t>> : std::false_type {};


REFLECTABLE_DECLARATION(eightrefl::deleter_t)
    REFLECTABLE_REGISTRY(eightrefl::dev())
REFLECTABLE_DECLARATION_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE

#endif // EIGHTREFL_DEV_DELETER_HPP
