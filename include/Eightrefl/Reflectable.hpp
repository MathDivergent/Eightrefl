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
    template <class InjectionType> static void evaluate(InjectionType& injection) { \
        auto xxtype = eightrefl::find_or_add_type<R>(injection); \
        [[maybe_unused]] auto xxmeta = &xxtype->meta; \
        eightrefl::add_injections_using_keys<R>(xxtype);

#ifdef EIGHTREFL_DISABLE_REFLECTION_FIXTURE
    #define REFLECTABLE_INIT() \
            } \
        };
#else
    #define REFLECTABLE_INIT() \
            } \
            inline static auto xxfixture = eightrefl::fixture<R>(); \
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

    static_assert
    (
        meta::is_complete<reflectable_traits>::value,
        "name_of: reflection declaration for this type not found"
    );

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

    static_assert
    (
        meta::is_complete<reflectable_traits>::value,
        "registry_of: reflection declaration for this type not found"
    );

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
    static auto xxlock = false; if (xxlock) return;
    xxlock = true;

    auto xxinjectable = injectable_t{};
    ::xxeightrefl<ReflectableType>::evaluate(xxinjectable);
}

template <typename ReflectableType>
ReflectableType&& reflectable(ReflectableType&& object)
{
    reflectable<std::decay_t<ReflectableType>>();
    return std::forward<ReflectableType>(object);
}

template <typename ReflectableType>
bool fixture()
{
    static_assert
    (
        meta::is_complete<::xxeightrefl_traits<ReflectableType>>::value,
        "fixture: reflection declaration for this type not found"
    );

    if constexpr (::xxeightrefl_traits_has_reflectable_lazy_evaluate<ReflectableType>::value)
    {
        return false;
    }
    else
    {
        reflectable<ReflectableType>();
        return true;
    }
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

template <typename DirtyReflectableType,
          class InjectionType>
type_t* find_or_add_type(InjectionType& injection)
{
    auto xxtype = find_or_add_type<DirtyReflectableType>();
    injection.template type<DirtyReflectableType>(*xxtype);

    return xxtype;
}

template <typename ReflectableType, typename ParentReflectableType>
parent_t* find_or_add_parent(type_t* type)
{
    static_assert
    (
        std::is_base_of_v<ParentReflectableType, ReflectableType>,
        "find_or_add_parent: ReflectableType must derive from ParentReflectableType"
    );

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

template <typename ReflectableType, typename ParentReflectableType,
          class InjectionType>
parent_t* find_or_add_parent(type_t* type, InjectionType& injection)
{
    auto xxparent = find_or_add_parent<ReflectableType, ParentReflectableType>(type);
    injection.template parent<ReflectableType, ParentReflectableType>(*xxparent);

    return xxparent;
}

namespace detail
{

template <typename ReturnType, typename... ArgumentTypes>
auto function_argument_types(ReturnType(*)(ArgumentTypes...))
{
    return std::vector<type_t*>({ find_or_add_type<ArgumentTypes>()... });
}

template <typename ReturnType, typename... ArgumentTypes>
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

template <typename ReflectableType,
          typename DirtyFactoryType,
          class InjectionType>
factory_t* find_or_add_factory(type_t* type, InjectionType& injection)
{
    using function_traits = meta::function_traits<DirtyFactoryType>;

    auto xxfactory = find_or_add_factory<DirtyFactoryType>(type);
    injection.template factory<ReflectableType, typename function_traits::type_pointer>(*xxfactory);

    return xxfactory;
}

template <typename DirtyFunctionType = void, typename FunctionTypePointer>
function_t* find_or_add_function(type_t* type, std::string const& name, FunctionTypePointer pointer)
{
    using function_traits = meta::function_traits
    <
        typename meta::mark_dirty<FunctionTypePointer, DirtyFunctionType>::type
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

template <typename ReflectableType,
          typename DirtyFunctionType = void, typename FunctionTypePointer,
          class InjectionType>
function_t* find_or_add_function(type_t* type, std::string const& name, FunctionTypePointer pointer, InjectionType& injection)
{
    auto xxfunction = find_or_add_function<DirtyFunctionType>(type, name, pointer);
    injection.template function<ReflectableType, FunctionTypePointer>(*xxfunction);

    return xxfunction;
}

template <typename IODirtyType = void, typename ODirtyType = void /*unused*/,
          typename ITypePointer, typename OTypePointer>
property_t* find_or_add_property(type_t* type, std::string const& name, ITypePointer ipointer, OTypePointer opointer)
{
    using property_traits = meta::property_traits
    <
        typename std::conditional_t
        <
            std::is_null_pointer_v<ITypePointer>,
            meta::mark_dirty<OTypePointer, IODirtyType>,
            meta::mark_dirty<ITypePointer, IODirtyType>
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

template <typename ReflectableType,
          typename IODirtyType = void, typename ODirtyType = void,
          typename ITypePointer, typename OTypePointer,
          class InjectionType>
property_t* find_or_add_property(type_t* type, std::string const& name, ITypePointer ipointer, OTypePointer opointer, InjectionType& injection)
{
    auto xxproperty = find_or_add_property<IODirtyType, ODirtyType>(type, name, ipointer, opointer);
    injection.template property<ReflectableType, ITypePointer, OTypePointer>(*xxproperty);

    return xxproperty;
}

template <typename BitfieldType>
property_t* find_or_add_bitfield(type_t* type, std::string const& name,
                                 std::function<void(std::any const&, std::any&)> ihandler,
                                 std::function<void(std::any const&, std::any const&)> ohandler)
{
    auto xxmeta = type->property.find(name);
    if (xxmeta == nullptr) xxmeta = type->property.add
    (
        name,
        {
            .name = name,
            .type = find_or_add_type<BitfieldType>(),
            .get = ihandler,
            .set = ohandler
        }
    );

    return xxmeta;
}

template <typename ReflectableType,
          typename BitfieldType,
          class InjectionType>
property_t* find_or_add_bitfield(type_t* type, std::string const& name,
                                 std::function<void(std::any const&, std::any&)> ihandler,
                                 std::function<void(std::any const&, std::any const&)> ohandler,
                                 InjectionType& injection)
{
    auto xxproperty = find_or_add_bitfield<BitfieldType>(type, name, ihandler, ohandler);
    injection.template bitfield<ReflectableType, BitfieldType>(*xxproperty);

    return xxproperty;
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

template <typename ReflectableType,
          typename DirtyDeleterType,
          class InjectionType>
deleter_t* find_or_add_deleter(type_t* type, InjectionType& injection)
{
    using deleter_traits = eightrefl::meta::deleter_traits<DirtyDeleterType>;

    auto xxdeleter = eightrefl::find_or_add_deleter<DirtyDeleterType>(type);
    injection.template deleter<ReflectableType, typename deleter_traits::type_pointer>(*xxdeleter);

    return xxdeleter;
}

template <typename MetaType>
meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name, MetaType&& value)
{
    auto xxmeta = meta.find(name);
    if (xxmeta == nullptr) xxmeta = meta.add
    (
        name,
        {
            .name = name,
            .value = value
        }
    );

    return xxmeta;
}

template <typename ReflectableType,
          typename MetaType,
          class InjectionType>
meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name, MetaType&& value, InjectionType& injection)
{
    auto xxmeta = find_or_add_meta(meta, name, std::forward<MetaType>(value));
    injection.template meta<ReflectableType, MetaType>(*xxmeta);

    return xxmeta;
}

inline meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name)
{
    auto xxmeta = meta.find(name);
    if (xxmeta == nullptr) xxmeta = meta.add
    (
        name,
        {
            .name = name
        }
    );

    return xxmeta;
}

template <typename ReflectableType,
          class InjectionType>
meta_t* find_or_add_meta(attribute_t<meta_t>& meta, std::string const& name, InjectionType& injection)
{
    auto xxmeta = find_or_add_meta(meta, name);
    injection.template meta<ReflectableType, void>(*xxmeta);

    return xxmeta;
}

template <typename ReflectableType, class InjectionType>
injection_t* find_or_add_injection(type_t* type)
{
    static_assert
    (
        std::is_base_of_v<injectable_t, InjectionType>,
        "find_or_add_injection: InjectionType must derive from injectable_t"
    );

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
