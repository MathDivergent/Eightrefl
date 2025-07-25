#ifdef EIGHTREFL_STANDARD_ENABLE
#ifdef EIGHTREFL_RTTI_ENABLE
#include <Eightrefl/Standard/typeindex.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// as function argument type
#include <Eightrefl/Standard/typeinfo.hpp>

#if __cplusplus > 201703L
#include <Eightrefl/Standard/compare.hpp>
#endif // if

REFLECTABLE(std::type_index)
    FACTORY(R(std::type_info const&))

#if __cplusplus > 201703L
    FUNCTION(operator<=>)
#else
    FUNCTION(operator==)
    FUNCTION(operator!=)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator<)
    FUNCTION(operator<=)
    FUNCTION(operator>)
    FUNCTION(operator>=)
    #endif // EIGHTREFL_FULLY_ENABLE
#endif // if
    FUNCTION(hash_code)
    FUNCTION(name)
REFLECTABLE_INIT()
#endif // EIGHTREFL_RTTI_ENABLE
#endif // EIGHTREFL_STANDARD_ENABLE
