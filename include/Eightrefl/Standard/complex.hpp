#ifndef EIGHTREFL_STANDARD_COMPLEX_HPP
#define EIGHTREFL_STANDARD_COMPLEX_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <complex> // complex

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

template <typename> struct xxeightrefl_std_complex_pass_value;

template <typename ValueType>
struct xxeightrefl_std_complex_pass_value<std::complex<ValueType>>
{
    using type = ValueType const&;
};

template <> struct xxeightrefl_std_complex_pass_value<std::complex<float>> { using type = float; };
template <> struct xxeightrefl_std_complex_pass_value<std::complex<double>> { using type = double; };
template <> struct xxeightrefl_std_complex_pass_value<std::complex<long double>> { using type = long double; };

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ValueType>,
    std::complex<ValueType>, std::complex<eightrefl::clean_of<ValueType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::complex<ValueType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::complex<" + eightrefl::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ValueType>, std::complex<ValueType>)
    FACTORY(R())
    FACTORY(R(typename xxeightrefl_std_complex_pass_value<R>::type, typename xxeightrefl_std_complex_pass_value<R>::type))
    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator+=, R&(typename xxeightrefl_std_complex_pass_value<R>::type))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator+=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator-=, R&(typename xxeightrefl_std_complex_pass_value<R>::type))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator-=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator*=, R&(typename xxeightrefl_std_complex_pass_value<R>::type))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator*=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator/=, R&(typename xxeightrefl_std_complex_pass_value<R>::type))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator/=, R&(R const&))
    PROPERTY(real)
    PROPERTY(imag)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_COMPLEX_HPP
