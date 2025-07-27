#ifdef EIGHTREFL_STANDARD_ENABLE
#ifdef EIGHTREFL_RTTI_ENABLE
#include <Eightrefl/Standard/typeinfo.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

REFLECTABLE(std::type_info)
    FUNCTION(operator==)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(before)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(hash_code)
    FUNCTION(name)
REFLECTABLE_INIT()
#endif // EIGHTREFL_RTTI_ENABLE
#endif // EIGHTREFL_STANDARD_ENABLE
