#include <Eightrefl/Standard/complex.hpp>

template struct ::xxeightrefl<std::complex<float>>;

#ifdef EIGHTREFL_FULLY_ENABLE
template struct ::xxeightrefl<std::complex<double>>;
template struct ::xxeightrefl<std::complex<long double>>;
#endif // EIGHTREFL_FULLY_ENABLE
