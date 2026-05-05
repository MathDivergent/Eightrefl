#ifndef EIGHTREFL_TRAITS_DELETER_HPP
#define EIGHTREFL_TRAITS_DELETER_HPP

#include <Eightrefl/Traits/Dirty.hpp>

template <typename>
struct xxeightrefl_deleter_traits;

template <typename ReturnType, typename ReflectableType>
struct xxeightrefl_deleter_traits<ReturnType(ReflectableType)>
{
    using dirty_type = ReturnType(ReflectableType);
    using dirty_type_pointer = ReturnType(*)(ReflectableType);

    using type = typename ::xxeightrefl_dirty_traits<ReturnType>::R(typename ::xxeightrefl_dirty_traits<ReflectableType>::R);
    using type_pointer = typename ::xxeightrefl_dirty_traits<ReturnType>::R(*)(typename ::xxeightrefl_dirty_traits<ReflectableType>::R);
};

template <typename ReturnType, typename ReflectableType>
struct xxeightrefl_deleter_traits<ReturnType(*)(ReflectableType)> : xxeightrefl_deleter_traits<ReturnType(ReflectableType)> {};

#endif // EIGHTREFL_TRAITS_DELETER_HPP
