#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Dev/Injection.hpp>
#include <Eightrefl/Dev/Type.hpp>

#include <Eightrefl/Standard/any.hpp>
#include <Eightrefl/Standard/function.hpp>

REFLECTABLE(eightrefl::injection_t)
    PROPERTY(type)
    PROPERTY(call)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE
