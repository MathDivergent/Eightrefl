#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Standard/char_traits.hpp>

template struct ::xxeightrefl<std::char_traits<char>>;

template struct ::xxeightrefl<std::char_traits<wchar_t>>;

#ifdef EIGHTREFL_FULLY_ENABLE
#if __cplusplus >= 202002L
template struct ::xxeightrefl<std::char_traits<char8_t>>;
#endif // if

template struct ::xxeightrefl<std::char_traits<char16_t>>;

template struct ::xxeightrefl<std::char_traits<char32_t>>;
#endif // EIGHTREFL_FULLY_ENABLE
#endif // EIGHTREFL_STANDARD_ENABLE
