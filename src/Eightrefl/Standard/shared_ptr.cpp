#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Standard/shared_ptr.hpp>

REFLECTABLE(std::shared_ptr<void>)
    FACTORY(R())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(std::nullptr_t))
    #endif // EIGHTREFL_FULLY_ENABLE

    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(reset, void())
    FUNCTION(get)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(use_count)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator bool)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
