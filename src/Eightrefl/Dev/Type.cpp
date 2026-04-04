#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Dev/Type.hpp>
#include <Eightrefl/Dev/Registry.hpp>

#include <Eightrefl/Dev/Injection.hpp>
#include <Eightrefl/Dev/Child.hpp>

#include <Eightrefl/Dev/Parent.hpp>
#include <Eightrefl/Dev/Factory.hpp>
#include <Eightrefl/Dev/Function.hpp>
#include <Eightrefl/Dev/Property.hpp>
#include <Eightrefl/Dev/Deleter.hpp>
#include <Eightrefl/Dev/Meta.hpp>
#include <Eightrefl/Dev/Attribute.hpp>

#include <Eightrefl/Standard/string.hpp>
#include <Eightrefl/Standard/any.hpp>
#include <Eightrefl/Standard/function.hpp>

REFLECTABLE(eightrefl::type_t)
    PROPERTY(name)
    PROPERTY(registry)
    PROPERTY(size)
    PROPERTY(context)

    PROPERTY(injection)
    PROPERTY(child)

    PROPERTY(parent)
    PROPERTY(factory)
    PROPERTY(function)
    PROPERTY(property)
    PROPERTY(deleter)
    PROPERTY(meta)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE
