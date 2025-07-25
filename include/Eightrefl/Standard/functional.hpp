#ifndef EIGHTREFL_STANDARD_FUNCTIONAL_HPP
#define EIGHTREFL_STANDARD_FUNCTIONAL_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <functional> // hash

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename KeyType>,
    std::hash<KeyType>, std::hash<eightrefl::clean_of<KeyType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename KeyType>, std::hash<KeyType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::hash<" + eightrefl::name_of<KeyType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename KeyType>, std::hash<KeyType>)
    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R())
    FACTORY(R(R const&))
    FUNCTION(operator())
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()

TEMPLATE_REFLECTABLE_CLEAN(template <typename T>, std::equal_to<T>, std::equal_to<eightrefl::clean_of<T>>)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, std::equal_to<T>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::equal_to<" + eightrefl::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, std::equal_to<T>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_CLEAN(template <typename T>, std::less<T>, std::less<eightrefl::clean_of<T>>)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, std::less<T>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::less<" + eightrefl::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, std::less<T>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_CLEAN(template <typename T>, std::greater<T>, std::greater<eightrefl::clean_of<T>>)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename T>, std::greater<T>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::greater<" + eightrefl::name_of<T>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename T>, std::greater<T>)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_BUILTIN_FUNCTIONAL_HPP
