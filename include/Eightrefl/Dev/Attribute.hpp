#ifndef EIGHTREFL_DEV_ATTRIBUTE_HPP
#define EIGHTREFL_DEV_ATTRIBUTE_HPP

#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/string.hpp>
#include <Eightrefl/Standard/unordered_map.hpp>

#include <Eightrefl/Dev/Dev.hpp>

TEMPLATE_REFLECTABLE_DECLARATION((template <typename MetaType>), eightrefl::attribute_t<MetaType>)
    REFLECTABLE_REGISTRY(eightrefl::dev())
    REFLECTABLE_NAME("eightrefl::attribute_t<" + eightrefl::name_of<MetaType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename MetaType>), eightrefl::attribute_t<MetaType>)
    FUNCTION(find)
    FUNCTION(add)
    PROPERTY(all)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE

#endif // EIGHTREFL_DEV_ATTRIBUTE_HPP
