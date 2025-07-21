#ifdef EIGHTREFL_DEV_ENABLE
#include <Eightrefl/Dev/Reflection.hpp>
#include <Eightrefl/Dev/Parent.hpp>
#include <Eightrefl/Dev/Factory.hpp>
#include <Eightrefl/Dev/Function.hpp>
#include <Eightrefl/Dev/Property.hpp>
#include <Eightrefl/Dev/Deleter.hpp>
#include <Eightrefl/Dev/Meta.hpp>
#include <Eightrefl/Dev/Attribute.hpp>

#include <Eightrefl/Standard/string.hpp>

REFLECTABLE(eightrefl::reflection_t)
    PROPERTY(name)
    PROPERTY(parent)
    PROPERTY(function)
    PROPERTY(factory)
    PROPERTY(property)
    PROPERTY(meta)
REFLECTABLE_INIT()
#endif // EIGHTREFL_DEV_ENABLE
