#ifndef EIGHTREFL_BUILTIN_BUILITIN_CPP
#define EIGHTREFL_BUILTIN_BUILITIN_CPP

#ifndef __cpp_lib_type_identity
namespace std
{

template <typename T> struct type_identity { using type = T; };
template <typename T> using type_identity_t = typename type_identity<T>::type;

} // namespace std
#endif // __cpp_lib_type_identity

namespace eightrefl
{

struct registry_t;

extern EIGHTREFL_API registry_t* builtin();

} // namespace eightrefl

#endif // EIGHTREFL_BUILTIN_BUILITIN_CPP
