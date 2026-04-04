#ifndef EIGHTREFL_STANDARD_STANDARD_CPP
#define EIGHTREFL_STANDARD_STANDARD_CPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Detail/Meta.hpp>

#define REFLECTABLE_STANDARD() struct xxstandard;

template <typename, typename enable = void> struct xxeightrefl_traits_has_reflectable_standard : std::false_type {};
template <typename ReflectableType>
struct xxeightrefl_traits_has_reflectable_standard<ReflectableType, std::void_t<typename ::xxeightrefl_traits<ReflectableType>::xxstandard>> : std::true_type {};


namespace eightrefl
{

struct registry_t;

extern EIGHTREFL_API registry_t* standard();

} // namespace eightrefl
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_STANDARD_CPP
