#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Standard/any.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// as function return type
#include <Eightrefl/Standard/typeinfo.hpp>

REFLECTABLE(std::any)
    FACTORY(R())
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(reset)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(has_value)
    #ifdef EIGHTREFL_RTTI_ENABLE
    FUNCTION(type)
    #endif // EIGHTREFL_RTTI_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
