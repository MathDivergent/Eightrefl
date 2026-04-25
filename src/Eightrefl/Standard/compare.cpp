#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Standard/compare.hpp>

#include <Eightrefl/Reflectable.hpp>

#if __cplusplus > 201703L
REFLECTABLE(std::partial_ordering)
REFLECTABLE_INIT()

REFLECTABLE(std::weak_ordering)
REFLECTABLE_INIT()

REFLECTABLE(std::strong_ordering)
REFLECTABLE_INIT()
#endif // if
#endif // EIGHTREFL_STANDARD_ENABLE
