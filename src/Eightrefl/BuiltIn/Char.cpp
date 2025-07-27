#include <Eightrefl/BuiltIn/Char.hpp>
#include <Eightrefl/BuiltIn/Function.hpp>

REFLECTABLE(char)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(wchar_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

#if __cplusplus >= 202002L
REFLECTABLE(char8_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
#endif // if

REFLECTABLE(char16_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()

REFLECTABLE(char32_t)
    FACTORY(R())
    FACTORY(R(R))
REFLECTABLE_INIT()
