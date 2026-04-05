#ifndef EIGHTREFL_BUILTIN_BUILITIN_CPP
#define EIGHTREFL_BUILTIN_BUILITIN_CPP

#include <Eightrefl/Detail/Meta.hpp>

#define REFLECTABLE_BUILTIN() \
    struct xxbuiltin;


template <typename, typename enable = void> struct xxeightrefl_traits_has_reflectable_builtin : std::false_type {};
template <typename ReflectableType>
struct xxeightrefl_traits_has_reflectable_builtin<ReflectableType, std::void_t<typename ::xxeightrefl_traits<ReflectableType>::xxbuiltin>> : std::true_type {};


namespace eightrefl
{

struct registry_t;

extern EIGHTREFL_API registry_t* builtin();

} // namespace eightrefl

#endif // EIGHTREFL_BUILTIN_BUILITIN_CPP
