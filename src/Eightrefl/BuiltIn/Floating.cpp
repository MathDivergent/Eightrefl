#include <Eightrefl/BuiltIn/Floating.hpp>
#include <Eightrefl/BuiltIn/Function.hpp>

REFLECTABLE(float)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(double)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(long double)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
