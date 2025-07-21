#ifdef EIGHTREFL_DEV_ENABLE
#include <Eightrefl/Dev/Injection.hpp>
#include <Eightrefl/Dev/Type.hpp>

#include <Eightrefl/Standard/string.hpp>
#include <Eightrefl/Standard/any.hpp>
#include <Eightrefl/Standard/function.hpp>

REFLECTABLE(eightrefl::injection_t)
    PROPERTY(name)
    PROPERTY(type)
    PROPERTY(call)
REFLECTABLE_INIT()
#endif // EIGHTREFL_DEV_ENABLE
