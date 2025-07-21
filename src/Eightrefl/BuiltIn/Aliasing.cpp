#include <Eightrefl/BuiltIn/Aliasing.hpp>
#include <Eightrefl/BuiltIn/Function.hpp>

REFLECTABLE(std_size_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(std_ptrdiff_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
