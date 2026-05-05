#ifndef EIGHTREFL_PROPERTY_HPP
#define EIGHTREFL_PROPERTY_HPP

#include <string> // string
#include <any> // any, any_cast
#include <utility> // pair
#include <functional> // function
#include <memory> // addressof
#include <type_traits> // is_copy_assignable_v, is_reference_v

#include <Eightrefl/Attribute.hpp>
#include <Eightrefl/Meta.hpp>
#include <Eightrefl/Utility.hpp>

#include <Eightrefl/Traits/Access.hpp>
#include <Eightrefl/Traits/Property.hpp>

#include <Eightrefl/Detail/Macro.hpp>

#define EIGHTREFL_PROPERTY_IMPL(scope, external_name, internal_iname, internal_oname, ... /*variable_type_or_function_type(s)*/) \
    { \
        auto [xxi, xxo] = ::xxeightrefl_access_traits<scope>::template property<__VA_ARGS__>::of(&scope::EIGHTREFL_DEPAREN(internal_iname), &scope::EIGHTREFL_DEPAREN(internal_oname)); \
        auto xxproperty = eightrefl::find_or_add_property<CleanR __VA_OPT__(, __VA_ARGS__)>(xxtype, external_name, xxi, xxo, injection); \
        xxmeta = &xxproperty->meta; \
    }


#define PROPERTY_AS(external_name, internal_iname, internal_oname, ... /*variable_type_or_function_type(s)*/) \
    EIGHTREFL_PROPERTY_IMPL(CleanR, external_name, internal_iname, internal_oname, __VA_ARGS__)

#define PROPERTY(name, ... /*variable_type_or_function_type*/) \
    PROPERTY_AS(EIGHTREFL_TO_STRING(name), name, name, __VA_ARGS__)

#define EXTERNAL_PROPERTY_AS(external_name, internal_iname, internal_oname, ... /*variable_type_or_function_type(s)*/) \
    EIGHTREFL_PROPERTY_IMPL(, external_name, internal_iname, internal_oname, __VA_ARGS__)

#define EXTERNAL_PROPERTY(name, ... /*variable_type_or_function_type(s)*/) \
    EXTERNAL_PROPERTY_AS(EIGHTREFL_TO_STRING(name), name, name, __VA_ARGS__)


#define BITFIELD_AS(external_name, internal_name) \
    { \
        using xxbitfield_type = std::decay_t<decltype(std::declval<CleanR>().internal_name)>; \
        auto xxi = [](std::any const& context) -> std::any { return xxbitfield_type(std::any_cast<CleanR*>(context)->internal_name); }; \
        auto xxo = [](std::any const& context, std::any const& value) { std::any_cast<CleanR*>(context)->internal_name = std::any_cast<xxbitfield_type>(value); }; \
        auto xxproperty = eightrefl::find_or_add_bitfield<CleanR, xxbitfield_type>(xxtype, external_name, xxi, xxo, injection); \
        xxmeta = &xxproperty->meta; \
    }

#define BITFIELD(name) \
    BITFIELD_AS(EIGHTREFL_TO_STRING(name), name)


namespace eightrefl
{

struct type_t;

struct EIGHTREFL_API property_t
{
    std::string const name{};
    type_t* const type = nullptr;
    std::function<std::any(std::any const& outer_context)> const get = nullptr;
    std::function<void(std::any const& outer_context, std::any const& value)> const set = nullptr;
    std::function<std::any(std::any const& outer_context)> const context = nullptr;
    std::pair<std::any, std::any> const pointer{};
    attribute_t<meta_t> meta{};
};

namespace detail
{

template <typename ReflectableType, typename ITypePointer>
auto handler_property_get(ITypePointer property)
{
    return [property](std::any const& outer_context) -> std::any
    {
        return utility::backward
        (
            (std::any_cast<ReflectableType*>(outer_context)->*property)()
        );
    };
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType ReflectableType::* property)
{
    #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    return [property](std::any const& outer_context) -> std::any
    {
        return utility::backward
        (
            std::any_cast<ReflectableType*>(outer_context)->*property
        );
    };
    #else
    if constexpr (::xxeightrefl_property_is_gettable<PropertyType>::value)
    {
        return [property](std::any const& outer_context) -> std::any
        {
            return std::any_cast<ReflectableType*>(outer_context)->*property;
        };
    }
    else
    {
        return nullptr;
    }
    #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void) const)
{
    return detail::handler_property_get<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void) const&)
{
    return detail::handler_property_get<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void))
{
    return detail::handler_property_get<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void)&)
{
    return detail::handler_property_get<ReflectableType>(property);
}

template <typename PropertyType>
auto handler_property_get(PropertyType* property)
{
    #ifdef EIGHTREFL_CANONICAL_PROPERTY_ENABLE
    return [property](std::any const&) -> std::any
    {
        // get of external (non-member) property
        return utility::backward(*property);
    };
    #else
    if constexpr (::xxeightrefl_property_is_gettable<PropertyType>::value)
    {
        return [property](std::any const&) -> std::any
        {
            // get of external (non-member) property
            return *property;
        };
    }
    else
    {
        return nullptr;
    }
    #endif // EIGHTREFL_CANONICAL_PROPERTY_ENABLE
}

template <typename PropertyType>
auto handler_property_get(PropertyType(* property)(void))
{
    return [property](std::any const&) -> std::any
    {
        return utility::backward(property());
    };
}

constexpr auto handler_property_get(std::nullptr_t)
{
    return nullptr;
}


namespace detail
{

template <typename ReflectableType, typename OTypePointer>
auto handler_property_set(OTypePointer property)
{
    using property_traits = ::xxeightrefl_property_traits<OTypePointer>;
    using forward_type = typename property_traits::forward_type;

    return [property](std::any const& outer_context, std::any const& value)
    {
        (std::any_cast<ReflectableType*>(outer_context)->*property)(utility::forward<forward_type>(value));
    };
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType ReflectableType::* property)
{
    if constexpr (::xxeightrefl_property_is_settable<PropertyType>::value)
    {
        using property_traits = ::xxeightrefl_property_traits<PropertyType ReflectableType::*>;
        using forward_type = typename property_traits::forward_type;

        return [property](std::any const& outer_context, std::any const& value)
        {
            std::any_cast<ReflectableType*>(outer_context)->*property = utility::forward<forward_type>(value);
        };
    }
    else
    {
        return nullptr;
    }
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(void(ReflectableType::* property)(PropertyType))
{
    return detail::handler_property_set<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(void(ReflectableType::* property)(PropertyType)&)
{
    return detail::handler_property_set<ReflectableType>(property);
}

template <typename PropertyType>
auto handler_property_set(PropertyType* property)
{
    if constexpr (::xxeightrefl_property_is_settable<PropertyType>::value)
    {
        using property_traits = ::xxeightrefl_property_traits<PropertyType*>;
        using forward_type = typename property_traits::forward_type;

        return [property](std::any const&, std::any const& value)
        {
            // set of external (non-member) property
            *property = utility::forward<forward_type>(value);
        };
    }
    else
    {
        return nullptr;
    }
}

template <typename PropertyType>
auto handler_property_set(void(* property)(PropertyType))
{
    using property_traits = ::xxeightrefl_property_traits<void(*)(PropertyType)>;
    using forward_type = typename property_traits::forward_type;

    return [property](std::any const&, std::any const& value)
    {
        property(utility::forward<forward_type>(value));
    };
}

constexpr auto handler_property_set(std::nullptr_t)
{
    return nullptr;
}


namespace detail
{

template <typename ReflectableType, typename ITypePointer>
auto handler_property_context(ITypePointer property)
{
    using property_traits = ::xxeightrefl_property_traits<ITypePointer>;
    using property_type = typename property_traits::type;

    if constexpr (std::is_reference_v<property_type>)
    {
        return [property](std::any const& outer_context) -> std::any
        {
            return const_cast<typename detail::to_reflectable_reference<property_type>::type>
            (
                std::addressof((std::any_cast<ReflectableType*>(outer_context)->*property)())
            );
        };
    }
    else
    {
        // context to non-reference return type is not allowed
        return nullptr;
    }
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType ReflectableType::* property)
{
    return [property](std::any const& outer_context) -> std::any
    {
        return const_cast<typename detail::to_reflectable_object<PropertyType>::type*>
        (
            // context to member property
            std::addressof(std::any_cast<ReflectableType*>(outer_context)->*property)
        );
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void) const)
{
    return detail::handler_property_context<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void) const&)
{
    return detail::handler_property_context<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void))
{
    return detail::handler_property_context<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void)&)
{
    return detail::handler_property_context<ReflectableType>(property);
}

template <typename PropertyType>
auto handler_property_context(PropertyType* property)
{
    return [property](std::any const&) -> std::any
    {
        // context of external (non-member) property
        return const_cast<typename detail::to_reflectable_object<PropertyType>::type*>(property);
    };
}

template <typename PropertyType>
auto handler_property_context(PropertyType(* property)(void))
{
    if constexpr (std::is_reference_v<PropertyType>)
    {
        return [property](std::any const&) -> std::any
        {
            return const_cast<typename detail::to_reflectable_reference<PropertyType>::type>
            (
                std::addressof(property())
            );
        };
    }
    else
    {
        // context to non-reference return type is not allowed
        return nullptr;
    }
}

constexpr auto handler_property_context(std::nullptr_t)
{
    return nullptr;
}


template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType ReflectableType::* iproperty, PropertyType ReflectableType::* oproperty)
{
    if constexpr (::xxeightrefl_property_is_settable<PropertyType>::value)
    {
        return std::make_pair(iproperty, oproperty);
    }
    else
    {
        return std::make_pair(iproperty, std::any{});
    }
}

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void) const, void(ReflectableType::* oproperty)(OPropertyType))
{
    return std::make_pair(iproperty, oproperty);
}

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void) const, void(ReflectableType::* oproperty)(OPropertyType)&)
{
    return std::make_pair(iproperty, oproperty);
}

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void) const&, void(ReflectableType::* oproperty)(OPropertyType))
{
    return std::make_pair(iproperty, oproperty);
}

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void) const&, void(ReflectableType::* oproperty)(OPropertyType)&)
{
    return std::make_pair(iproperty, oproperty);
}

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void), void(ReflectableType::* oproperty)(OPropertyType))
{
    return std::make_pair(iproperty, oproperty);
}

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void), void(ReflectableType::* oproperty)(OPropertyType)&)
{
    return std::make_pair(iproperty, oproperty);
}

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void)&, void(ReflectableType::* oproperty)(OPropertyType))
{
    return std::make_pair(iproperty, oproperty);
}

template <typename ReflectableType, typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(ReflectableType::* iproperty)(void)&, void(ReflectableType::* oproperty)(OPropertyType)&)
{
    return std::make_pair(iproperty, oproperty);
}

template <typename PropertyType>
constexpr auto property_pointer(PropertyType* iproperty, PropertyType* oproperty)
{
    if constexpr (::xxeightrefl_property_is_settable<PropertyType>::value)
    {
        return std::make_pair(iproperty, oproperty);
    }
    else
    {
        return std::make_pair(iproperty, std::any{});
    }
}

template <typename IPropertyType, typename OPropertyType>
constexpr auto property_pointer(IPropertyType(* iproperty)(void), void(* oproperty)(OPropertyType))
{
    return std::make_pair(iproperty, oproperty);
}


template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType ReflectableType::* iproperty, std::nullptr_t)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void) const, std::nullptr_t)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void) const&, std::nullptr_t)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void), std::nullptr_t)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(PropertyType(ReflectableType::* iproperty)(void)&, std::nullptr_t)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename PropertyType>
constexpr auto property_pointer(PropertyType* iproperty, std::nullptr_t)
{
    return std::make_pair(iproperty, std::any{});
}

template <typename PropertyType>
constexpr auto property_pointer(PropertyType(* iproperty)(void), std::nullptr_t)
{
    return std::make_pair(iproperty, std::any{});
}


template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType ReflectableType::* oproperty)
{
    return std::make_pair(std::any{}, oproperty);
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType(ReflectableType::* oproperty)(void))
{
    return std::make_pair(std::any{}, oproperty);
}

template <typename ReflectableType, typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType(ReflectableType::* oproperty)(void)&)
{
    return std::make_pair(std::any{}, oproperty);
}

template <typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType* oproperty)
{
    return std::make_pair(std::any{}, oproperty);
}

template <typename PropertyType>
constexpr auto property_pointer(std::nullptr_t, PropertyType(* oproperty)(void))
{
    return std::make_pair(std::any{}, oproperty);
}

} // namespace eightrefl

#endif // EIGHTREFL_PROPERTY_HPP
