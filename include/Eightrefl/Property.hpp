#ifndef EIGHTREFL_PROPERTY_HPP
#define EIGHTREFL_PROPERTY_HPP

#include <string> // string
#include <any> // any
#include <utility> // pair
#include <functional> // function
#include <memory> // addressof
#include <type_traits> // is_copy_assignable_v, is_reference_v

#include <Eightrefl/Attribute.hpp>
#include <Eightrefl/Meta.hpp>
#include <Eightrefl/Utility.hpp>

#include <Eightrefl/Detail/Macro.hpp> // EIGHTREFL_DEPAREN

// .property<R, variable_type_or_function_type>(external_name, &scope::internal_iname, &scope::ìnternal_oname)
#define EIGHTREFL_PROPERTY_IMPL(scope, external_name, internal_iname, internal_oname, ... /*variable_type_or_function_type(s)*/) \
    { \
        auto [xxi, xxo] = eightrefl::meta::access_traits<scope>::template property<__VA_ARGS__>::of(&scope::EIGHTREFL_DEPAREN(internal_iname), &scope::EIGHTREFL_DEPAREN(internal_oname)); \
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
        auto xxi = [](std::any const& context, std::any& result) { result = xxbitfield_type(std::any_cast<CleanR*>(context)->internal_name); }; \
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
    std::function<void(std::any const& context, std::any& result)> const get = nullptr;
    std::function<void(std::any const& context, std::any const& value)> const set = nullptr;
    std::function<std::any(std::any const& outer_context)> const context = nullptr;
    std::pair<std::any, std::any> const pointer{};
    attribute_t<meta_t> meta{};
};

namespace detail
{

template <typename ReflectableType, typename ITypePointer>
auto handler_property_get_impl(ITypePointer property)
{
    return [property](std::any const& context, std::any& value)
    {
        value = utility::backward
        (
            (std::any_cast<ReflectableType*>(context)->*property)()
        );
    };
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType ReflectableType::* property)
{
    return [property](std::any const& context, std::any& result)
    {
        result = utility::backward
        (
            std::any_cast<ReflectableType*>(context)->*property
        );
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void) const)
{
    return detail::handler_property_get_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void) const&)
{
    return detail::handler_property_get_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void))
{
    return detail::handler_property_get_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_get(PropertyType(ReflectableType::* property)(void)&)
{
    return detail::handler_property_get_impl<ReflectableType>(property);
}

template <typename PropertyType>
auto handler_property_get(PropertyType* property)
{
    return [property](std::any const&, std::any& result)
    {
        // get of external (non-member) property
        result = utility::backward(*property);
    };
}

template <typename PropertyType>
auto handler_property_get(PropertyType(* property)(void))
{
    return [property](std::any const&, std::any& result)
    {
        result = utility::backward(property());
    };
}

constexpr auto handler_property_get(std::nullptr_t)
{
    return nullptr;
}


namespace detail
{

template <typename ReflectableType, typename OTypePointer>
auto handler_property_set_impl(OTypePointer property)
{
    using property_type = typename meta::property_traits<OTypePointer>::type;
    return [property](std::any const& context, std::any const& value)
    {
        (std::any_cast<ReflectableType*>(context)->*property)(utility::forward<property_type>(value));
    };
}

} // namespace detail

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(PropertyType ReflectableType::* property)
{
    if constexpr (std::is_copy_assignable_v<PropertyType>)
    {
        return [property](std::any const& context, std::any const& value)
        {
            std::any_cast<ReflectableType*>(context)->*property = utility::forward<PropertyType>(value);
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
    return detail::handler_property_set_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_set(void(ReflectableType::* property)(PropertyType)&)
{
    return detail::handler_property_set_impl<ReflectableType>(property);
}

template <typename PropertyType>
auto handler_property_set(PropertyType* property)
{
    if constexpr (std::is_copy_assignable_v<PropertyType>)
    {
        return [property](std::any const&, std::any const& value)
        {
            // set of external (non-member) property
            *property = utility::forward<PropertyType>(value);
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
    return [property](std::any const&, std::any const& value)
    {
        property(utility::forward<PropertyType>(value));
    };
}

constexpr auto handler_property_set(std::nullptr_t)
{
    return nullptr;
}


namespace detail
{

template <typename ReflectableType, typename ITypePointer>
auto handler_property_context_impl(ITypePointer property)
{
    using property_type = typename meta::property_traits<ITypePointer>::type;
    if constexpr (std::is_reference_v<property_type>)
    {
        return [property](std::any const& outer_context) -> std::any
        {
            return const_cast<typename meta::to_reflectable_reference<property_type>::type>
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
        return const_cast<typename meta::to_reflectable_object<PropertyType>::type*>
        (
            // context to member property
            std::addressof(std::any_cast<ReflectableType*>(outer_context)->*property)
        );
    };
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void) const)
{
    return detail::handler_property_context_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void) const&)
{
    return detail::handler_property_context_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void))
{
    return detail::handler_property_context_impl<ReflectableType>(property);
}

template <typename ReflectableType, typename PropertyType>
auto handler_property_context(PropertyType(ReflectableType::* property)(void)&)
{
    return detail::handler_property_context_impl<ReflectableType>(property);
}

template <typename PropertyType>
auto handler_property_context(PropertyType* property)
{
    return [property](std::any const&) -> std::any
    {
        // context of external (non-member) property
        return const_cast<typename meta::to_reflectable_object<PropertyType>::type*>(property);
    };
}

template <typename PropertyType>
auto handler_property_context(PropertyType(* property)(void))
{
    if constexpr (std::is_reference_v<PropertyType>)
    {
        return [property](std::any const&) -> std::any
        {
            return const_cast<typename meta::to_reflectable_reference<PropertyType>::type>
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
    if constexpr (std::is_copy_assignable_v<PropertyType>)
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
    if constexpr (std::is_copy_assignable_v<PropertyType>)
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
