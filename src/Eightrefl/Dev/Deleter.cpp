#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Dev/Deleter.hpp>
#include <Eightrefl/Dev/Meta.hpp>
#include <Eightrefl/Dev/Attribute.hpp>

#include <Eightrefl/Standard/string.hpp>
#include <Eightrefl/Standard/any.hpp>
#include <Eightrefl/Standard/function.hpp>

REFLECTABLE(eightrefl::deleter_t)
    PROPERTY(name)
    PROPERTY(call)
    PROPERTY(meta)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE
