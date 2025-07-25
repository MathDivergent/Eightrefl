#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Standard/string.hpp>

template struct ::xxeightrefl<std::string>;

template struct ::xxeightrefl<std::wstring>;

#ifdef EIGHTREFL_FULLY_ENABLE
#if __cplusplus >= 202002L
template struct ::xxeightrefl<std::u8string>;
#endif // if

template struct ::xxeightrefl<std::u16string>;

template struct ::xxeightrefl<std::u32string>;
#endif // EIGHTREFL_FULLY_ENABLE
#endif // EIGHTREFL_STANDARD_ENABLE
