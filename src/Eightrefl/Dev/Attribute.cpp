#ifdef EIGHTREFL_DEV_ENABLE
#include <Eightrefl/Dev/Type.hpp>
#include <Eightrefl/Dev/Reflection.hpp>
#include <Eightrefl/Dev/Registry.hpp>
#include <Eightrefl/Dev/Injection.hpp>
#include <Eightrefl/Dev/Attribute.hpp>

#include <Eightrefl/Standard/string.hpp>
#include <Eightrefl/Standard/any.hpp>
#include <Eightrefl/Standard/function.hpp>

REFLECTABLE(eightrefl::type_t)
    PROPERTY(name)
    PROPERTY(reflection)
    PROPERTY(registry)
    PROPERTY(size)
    PROPERTY(context)
    PROPERTY(injection)
REFLECTABLE_INIT()
#endif // EIGHTREFL_DEV_ENABLE
