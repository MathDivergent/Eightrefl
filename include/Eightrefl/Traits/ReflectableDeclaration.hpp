#ifndef EIGHTREFL_TRAITS_REFLECTABLE_DECLARATION_HPP
#define EIGHTREFL_TRAITS_REFLECTABLE_DECLARATION_HPP

#include <type_traits> // false_type, void_t, true_type

template <typename ReflectableType, typename enable = void>
struct xxeightrefl_traits;

template <typename, typename enable = void> struct xxeightrefl_traits_has_reflectable_name : std::false_type {};
template <typename ReflectableType>
struct xxeightrefl_traits_has_reflectable_name<ReflectableType, std::void_t<decltype(&::xxeightrefl_traits<ReflectableType>::name)>> : std::true_type {};

template <typename, typename enable = void> struct xxeightrefl_traits_has_reflectable_registry : std::false_type {};
template <typename ReflectableType>
struct xxeightrefl_traits_has_reflectable_registry<ReflectableType, std::void_t<decltype(&::xxeightrefl_traits<ReflectableType>::registry)>> : std::true_type {};

template <typename, typename enable = void> struct xxeightrefl_traits_has_reflectable_lazy_evaluate : std::false_type {};
template <typename ReflectableType>
struct xxeightrefl_traits_has_reflectable_lazy_evaluate<ReflectableType, std::void_t<typename ::xxeightrefl_traits<ReflectableType>::xxlazy_evaluate>> : std::true_type {};

#endif // EIGHTREFL_TRAITS_REFLECTABLE_DECLARATION_HPP
