#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Dev/Factory.hpp>
#include <Eightrefl/Dev/Type.hpp>
#include <Eightrefl/Dev/Meta.hpp>
#include <Eightrefl/Dev/Attribute.hpp>

#include <Eightrefl/Standard/string.hpp>
#include <Eightrefl/Standard/any.hpp>
#include <Eightrefl/Standard/function.hpp>
#include <Eightrefl/Standard/vector.hpp>

REFLECTABLE(eightrefl::factory_t)
    PROPERTY(name)
    PROPERTY(call)
    PROPERTY(arguments)
    PROPERTY(result)
    PROPERTY(meta)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE
