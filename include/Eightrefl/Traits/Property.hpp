#ifndef EIGHTREFL_TRAITS_PROPERTY_HPP
#define EIGHTREFL_TRAITS_PROPERTY_HPP

#include <Eightrefl/Traits/Dirty.hpp>

template <typename PropertyType>
struct xxeightrefl_property_traits;

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(void)>
{
    using dirty_type = PropertyType;
    using type = typename ::xxeightrefl_dirty_traits<PropertyType>::R;

    using backward_type = void;
    using forward_type = type;

    using context_type = std::conditional_t
    <
        std::is_reference_v<type>,
        std::add_pointer_t<std::remove_const_t<std::remove_reference_t<type>>>,
        void
    >;
};

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(void) const> : xxeightrefl_property_traits<PropertyType(void)> {};

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(void) const&> : xxeightrefl_property_traits<PropertyType(void)> {};

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(void)&> : xxeightrefl_property_traits<PropertyType(void)> {};

template <typename PropertyType>
struct xxeightrefl_property_traits<void(PropertyType)>
{
    using dirty_type = PropertyType;
    using type = typename ::xxeightrefl_dirty_traits<PropertyType>::R;

    // using backward_type = ;
    using forward_type = type;

    using context_type = void;
};

template <typename PropertyType>
struct xxeightrefl_property_traits<void(PropertyType)&> : xxeightrefl_property_traits<void(PropertyType)> {};

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType*>
{
    using dirty_type = PropertyType;
    using type = typename ::xxeightrefl_dirty_traits<PropertyType>::R;

    // using backward_type = ;
    #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    using forward_type = type&;
    #else
    using forward_type = type;
    #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    using context_type = std::add_pointer_t<std::remove_const_t<type>>;
};

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(ReflectableType::*)(void) const> : xxeightrefl_property_traits<PropertyType(void) const> {};

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(ReflectableType::*)(void) const&> : xxeightrefl_property_traits<PropertyType(void) const&> {};

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(ReflectableType::*)(void)> : xxeightrefl_property_traits<PropertyType(void)> {};

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(ReflectableType::*)(void)&> : xxeightrefl_property_traits<PropertyType(void)&> {};

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<void(ReflectableType::*)(PropertyType)> : xxeightrefl_property_traits<void(PropertyType)> {};

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<void(ReflectableType::*)(PropertyType)&> : xxeightrefl_property_traits<void(PropertyType)&> {};

template <typename PropertyType>
struct xxeightrefl_property_traits<PropertyType(*)(void)> : xxeightrefl_property_traits<PropertyType(void)> {};

template <typename PropertyType>
struct xxeightrefl_property_traits<void(*)(PropertyType)> : xxeightrefl_property_traits<void(PropertyType)> {};

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_property_traits<PropertyType ReflectableType::*> : xxeightrefl_property_traits<PropertyType*> {};


template <typename PropertyType>
struct xxeightrefl_property_is_gettable : std::is_copy_constructible<PropertyType> {};

template <typename PropertyType>
struct xxeightrefl_property_is_settable : std::is_copy_assignable<PropertyType> {};

#endif // EIGHTREFL_TRAITS_PROPERTY_HPP
