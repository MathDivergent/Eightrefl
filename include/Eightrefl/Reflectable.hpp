#ifndef EIGHTREFL_REFLECTABLE_HPP
#define EIGHTREFL_REFLECTABLE_HPP

#include <cstddef> // size_t

#include <Eightrefl/Registry.hpp>
#include <Eightrefl/Type.hpp>

#include <Eightrefl/Detail/Meta.hpp>
#include <Eightrefl/Detail/Macro.hpp>

#define TEMPLATE_REFLECTABLE_DECLARATION(type_template_header, ... /*reflectable_type_template*/) \
    EIGHTREFL_DEPAREN(type_template_header) struct xxeightrefl_traits<__VA_ARGS__> { \
        using R = typename ::xxeightrefl_dirty<__VA_ARGS__>::R; \
        REFLECTABLE_LAZY_EVALUATE()

#define CONDITIONAL_REFLECTABLE_DECLARATION(... /*reflectable_type_condition*/) \
    template <typename DirtyR> struct xxeightrefl_traits<DirtyR, std::enable_if_t<__VA_ARGS__>> { \
        using R = typename ::xxeightrefl_dirty<DirtyR>::R; \
        REFLECTABLE_LAZY_EVALUATE()

#define REFLECTABLE_DECLARATION(... /*reflectable_type*/) \
    template <> struct xxeightrefl_traits<__VA_ARGS__> { \
        using R = typename ::xxeightrefl_dirty<__VA_ARGS__>::R; \
        [[maybe_unused]] static constexpr auto xxnative_name = #__VA_ARGS__;

#define REFLECTABLE_REGISTRY(... /*reflectable_registry_address*/) \
    static auto registry() { return __VA_ARGS__; }

#define REFLECTABLE_NAME(... /*reflectable_name_string*/) \
    static auto name() { return __VA_ARGS__; }

#define REFLECTABLE_LAZY_EVALUATE() \
    struct xxlazy_evaluate;

#define REFLECTABLE_DECLARATION_INIT() \
    };


#define TEMPLATE_REFLECTABLE(type_template_header, ... /*reflectable_type_template*/) \
    EIGHTREFL_DEPAREN(type_template_header) struct xxeightrefl<__VA_ARGS__> { \
        using R = __VA_ARGS__; \
        using CleanR = typename ::xxeightrefl_dirty<R>::R; \
        EIGHTREFL_REFLECTABLE_BODY()

#define CONDITIONAL_REFLECTABLE(... /*reflectable_type_condition*/) \
    template <typename R> struct xxeightrefl<R, std::enable_if_t<__VA_ARGS__>> { \
        using CleanR = typename ::xxeightrefl_dirty<R>::R; \
        EIGHTREFL_REFLECTABLE_BODY()

#define REFLECTABLE(... /*reflectable_type*/) \
    template <> struct xxeightrefl<__VA_ARGS__> { \
        using R = __VA_ARGS__; \
        using CleanR = typename ::xxeightrefl_dirty<R>::R; \
        EIGHTREFL_REFLECTABLE_BODY()

#define EIGHTREFL_REFLECTABLE_BODY() \
    template <class InjectionType> static void evaluate(InjectionType&& injection) { \
        auto xxtype = eightrefl::find_or_add_type<R>(); \
        [[maybe_unused]] auto xxmeta = &xxtype->meta; \
        eightrefl::add_injections_using_keys<R>(xxtype); \
        injection.template type<R>(*xxtype); \

#ifdef EIGHTREFL_DISABLE_REFLECTION_FIXTURE
    #define REFLECTABLE_INIT() \
            } \
        };
#else
    #define REFLECTABLE_INIT() \
            } \
            inline static auto xxfixture = (eightrefl::reflectable<R>(), true); \
        };
#endif // EIGHTREFL_DISABLE_REFLECTION_FIXTURE


#define REFLECTABLE_INJECTION_KEY(injection_key, ... /*reflectable_type*/) \
    template <> struct xxeightrefl_injection_traits<injection_key> { using R = __VA_ARGS__; }; \

#define TEMPLATE_REFLECTABLE_CLEAN(type_template_header, dirty_type, ... /*clean_reflectable_type_template*/) \
    EIGHTREFL_DEPAREN(type_template_header) struct xxeightrefl_dirty<EIGHTREFL_DEPAREN(dirty_type)> { using R = __VA_ARGS__; };

#define REFLECTABLE_CLEAN(dirty_type, ... /*clean_reflectable_type*/) \
    template <> struct xxeightrefl_dirty<dirty_type> { using R = __VA_ARGS__; };

#define TEMPLATE_REFLECTABLE_DIRTY(dirty_type_template_header, dirty_type, dirty_type_template, ... /*clean_reflectable_type_template*/) \
    EIGHTREFL_DEPAREN(dirty_type_template_header) struct dirty_type : eightrefl::meta::inherits<__VA_ARGS__> {}; \
    TEMPLATE_REFLECTABLE_CLEAN(dirty_type_template_header, dirty_type_template, __VA_ARGS__)

#define REFLECTABLE_DIRTY(dirty_type, ... /*clean_reflectable_type*/) \
    struct dirty_type final : eightrefl::meta::inherits<__VA_ARGS__> {}; \
    REFLECTABLE_CLEAN(dirty_type, __VA_ARGS__)


#define REFLECTABLE_ACCESS() \
    template <typename, typename> friend struct xxeightrefl;


namespace eightrefl
{

// useful for name generation (reflectable declaration)
template <typename ReflectableType>
std::string name_of()
{
    using reflectable_traits = ::xxeightrefl_traits<ReflectableType>;
    if constexpr (::xxeightrefl_traits_has_reflectable_name<ReflectableType>::value)
    {
        return reflectable_traits::name();
    }
    else
    {
        return reflectable_traits::xxnative_name;
    }
}

template <typename ReflectableType>
registry_t* registry_of()
{
    using reflectable_traits = ::xxeightrefl_traits<ReflectableType>;
    if constexpr (::xxeightrefl_traits_has_reflectable_registry<ReflectableType>::value)
    {
        return reflectable_traits::registry();
    }
    else
    {
        return global();
    }
}

template <typename ReflectableType>
using clean_of = typename ::xxeightrefl_dirty<ReflectableType>::R;


template <typename ReflectableType>
void reflectable()
{
    static auto lock = false; if (lock) return;
    lock = true;

    ::xxeightrefl<ReflectableType>::evaluate(injectable_t{});
}

template <typename ReflectableType>
ReflectableType&& reflectable(ReflectableType&& object)
{
    reflectable<std::decay_t<ReflectableType>>();
    return std::forward<ReflectableType>(object);
}


template <typename DirtyReflectableType>
type_t* find_or_add_type()
{
    using dirty_reflectable_type = typename std::conditional_t
    <
        std::is_reference_v<DirtyReflectableType>,
        meta::to_reflectable_reference<DirtyReflectableType>,
        std::conditional_t
        <
            std::is_pointer_v<DirtyReflectableType>,
            meta::to_reflectable_pointer<DirtyReflectableType>,
            meta::to_reflectable_object<DirtyReflectableType>
        >
    >::type;

    using reflectable_type = typename ::xxeightrefl_dirty<dirty_reflectable_type>::R;

    if constexpr (::xxeightrefl_traits_has_reflectable_lazy_evaluate<dirty_reflectable_type>::value)
    {
        reflectable<dirty_reflectable_type>();
    }

    auto xxname = name_of<dirty_reflectable_type>();
    auto xxregistry = registry_of<dirty_reflectable_type>();

    auto xxtype = xxregistry->all[xxname];
    if (xxtype == nullptr)
    {
        xxtype = xxregistry->template add<reflectable_type, dirty_reflectable_type>(xxname);
    }

    return xxtype;
}

template <typename ReflectableType, typename ParentReflectableType>
parent_t* find_or_add_parent(type_t* type)
{
    static_assert(std::is_base_of_v<ParentReflectableType, ReflectableType>);

    auto xxname = name_of<ParentReflectableType>();

    auto xxmeta = type->parent.find(xxname);
    if (xxmeta == nullptr)
    {
        auto xxtype = find_or_add_type<ParentReflectableType>();
        xxmeta = type->parent.add
        (
            xxname,
            {
                .type = xxtype,
                .cast = handler_parent_cast<ReflectableType, ParentReflectableType>()
            }
        );

        xxtype->child.add
        (
            type->name,
            {
                .type = type,
                .cast = handler_child_cast<ParentReflectableType, ReflectableType>()
            }
        );
    }

    return xxmeta;
}

namespace detail
{

template <typename... ArgumentTypes, typename ReturnType>
auto function_argument_types(ReturnType(*)(ArgumentTypes...))
{
    return std::vector<type_t*>({ find_or_add_type<ArgumentTypes>()... });
}

template <typename... ArgumentTypes, typename ReturnType>
auto function_return_type(ReturnType(*)(ArgumentTypes...))
{
    return find_or_add_type<ReturnType>();
}

} // namespace detail

template <typename DirtyFactoryType>
factory_t* find_or_add_factory(type_t* type)
{
    using function_traits = meta::function_traits<DirtyFactoryType>;
    using dirty_type = typename function_traits::dirty_type;
    using dirty_type_pointer = typename function_traits::dirty_type_pointer;
    using type_pointer = typename function_traits::type_pointer;

    auto xxname = name_of<dirty_type>();

    auto xxmeta = type->factory.find(xxname);
    if (xxmeta == nullptr) xxmeta = type->factory.add
    (
        xxname,
        {
            .name = xxname,
            .call = handler_factory_call(type_pointer{}),
            .arguments = detail::function_argument_types(dirty_type_pointer{}),
            .result = detail::function_return_type(dirty_type_pointer{})
        }
    );

    return xxmeta;
}

template <typename DirtyFunctionType = void, typename FunctionType>
function_t* find_or_add_function(type_t* type, std::string const& name, FunctionType pointer)
{
    using function_traits = meta::function_traits
    <
        typename std::conditional_t
        <
            std::is_void_v<DirtyFunctionType>,
            meta::type_identity<FunctionType>,
            meta::mark_dirty<FunctionType, DirtyFunctionType>
        >::type
    >;

    using dirty_type = typename function_traits::dirty_type;
    using dirty_type_pointer = typename function_traits::dirty_type_pointer;

    auto xxfunction = type->function.find(name);
    if (xxfunction == nullptr) xxfunction = type->function.add(name, {});

    auto xxoverload = name_of<dirty_type>();

    auto xxmeta = xxfunction->find(xxoverload);
    if (xxmeta == nullptr) xxmeta = xxfunction->add
    (
        xxoverload,
        {
            .name = xxoverload,
            .call = handler_function_call(pointer),
            .arguments = detail::function_argument_types(dirty_type_pointer{}),
            .result = detail::function_return_type(dirty_type_pointer{}),
            .pointer = pointer
        }
    );

    return xxmeta;
}

template <typename IDirtyPropertyType = void, typename ODirtyPropertyType = void /*unused*/,
          typename IPointerType, typename OPointerType>
property_t* find_or_add_property(type_t* type, std::string const& name, IPointerType ipointer, OPointerType opointer)
{
    using property_traits = meta::property_traits
    <
        typename std::conditional_t
        <
            std::is_void_v<IDirtyPropertyType>,
            meta::type_identity<IPointerType>,
            meta::mark_dirty<IPointerType, IDirtyPropertyType>
        >::type
    >;

    using dirty_type = typename property_traits::type;

    auto xxmeta = type->property.find(name);
    if (xxmeta == nullptr) xxmeta = type->property.add
    (
        name,
        {
            .name = name,
            .type = find_or_add_type<dirty_type>(),
            .get = handler_property_get(ipointer),
            .set = handler_property_set(opointer),
            .context = handler_property_context(ipointer),
            .pointer = property_pointer(ipointer, opointer)
        }
    );

    return xxmeta;
}

template <typename BitfieldType>
property_t* find_or_add_bitfield(type_t* type, std::string const& name,
                                 std::function<void(std::any const&, std::any&)> handler_get,
                                 std::function<void(std::any const&, std::any const&)> handler_set)
{
    auto xxmeta = type->property.find(name);
    if (xxmeta == nullptr) xxmeta = type->property.add
    (
        name,
        {
            .name = name,
            .type = find_or_add_type<BitfieldType>(),
            .get = handler_get,
            .set = handler_set
        }
    );

    return xxmeta;
}

template <typename DirtyDeleterType>
deleter_t* find_or_add_deleter(type_t* type)
{
    using deleter_traits = meta::deleter_traits<DirtyDeleterType>;
    using dirty_type = typename deleter_traits::dirty_type;
    using type_pointer = typename deleter_traits::type_pointer;

    auto xxname = name_of<dirty_type>();

    auto xxmeta = type->deleter.find(xxname);
    if (xxmeta == nullptr) xxmeta = type->deleter.add
    (
        xxname,
        {
            .name = xxname,
            .call = handler_deleter_call(type_pointer{})
        }
    );

    return xxmeta;
}

template <typename MetaType>
meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name, MetaType&& value)
{
    auto xxmeta = meta.find(name);
    if (xxmeta == nullptr) xxmeta = meta.add(name, { name, value });
    return xxmeta;
}

template <typename ReflectableType, class InjectionType>
injection_t* find_or_add_injection(type_t* type)
{
    static_assert(std::is_base_of_v<injectable_t, InjectionType>);

    auto xxtype = find_or_add_type<InjectionType>();

    auto xxmeta = type->injection.find(xxtype->name);
    if (xxmeta == nullptr) xxmeta = type->injection.add
    (
        xxtype->name,
        {
            .type = xxtype,
            .call = handler_injection_call<ReflectableType, InjectionType>()
        }
    );

    return xxmeta;
}


template <typename ReflectableType, std::size_t InjectionKeyValue = 0>
void add_injections_using_keys(type_t* type)
{
    if constexpr (InjectionKeyValue < xxeighrefl_injection_traits_max_key)
    {
        using injection_traits = ::xxeightrefl_injection_traits<InjectionKeyValue>;
        if constexpr (meta::is_complete<injection_traits>::value)
        {
            find_or_add_injection<ReflectableType, typename injection_traits::R>(type);
        }

        add_injections_using_keys<ReflectableType, InjectionKeyValue + 1>(type);
    }
}

} // namespace eightrefl

#endif // EIGHTREFL_REFLECTABLE_HPP
