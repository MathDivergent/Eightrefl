#include <Eightrefl/BuiltIn/Bool.hpp>
#include <Eightrefl/BuiltIn/Function.hpp>

#include <Eightrefl/Reflectable.hpp>

REFLECTABLE(bool)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
