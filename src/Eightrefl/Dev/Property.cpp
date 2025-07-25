#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Dev/Property.hpp>
#include <Eightrefl/Dev/Type.hpp>
#include <Eightrefl/Dev/Meta.hpp>
#include <Eightrefl/Dev/Attribute.hpp>

#include <Eightrefl/Standard/string.hpp>
#include <Eightrefl/Standard/any.hpp>
#include <Eightrefl/Standard/function.hpp>
#include <Eightrefl/Standard/pair.hpp>

REFLECTABLE(eightrefl::property_t)
    PROPERTY(name)
    PROPERTY(type)
    PROPERTY(get)
    PROPERTY(set)
    PROPERTY(context)
    PROPERTY(meta)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE
