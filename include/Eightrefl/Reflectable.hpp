#ifndef EIGHTREFL_REFLECTABLE_HPP
#define EIGHTREFL_REFLECTABLE_HPP

#include <Eightrefl/ReflectableDeclaration.hpp>
#include <Eightrefl/Type.hpp>

#include <Eightrefl/Traits/Function.hpp>
#include <Eightrefl/Traits/Property.hpp>
#include <Eightrefl/Traits/Deleter.hpp>

#include <Eightrefl/Detail/Macro.hpp>

#define EIGHTREFL_REFLECTABLE_BODY_IMPL() \
    template <class InjectionType> static void evaluate(InjectionType& injection) { \
        auto xxtype = eightrefl::find_or_add_type<R>(injection); \
        [[maybe_unused]] auto xxmeta = &xxtype->meta;


#define REFLECTABLE(... /*reflectable_type*/) \
    template <> struct xxeightrefl<__VA_ARGS__> { \
        using R = __VA_ARGS__; \
        using CleanR = typename ::xxeightrefl_dirty_traits<R>::R; \
        EIGHTREFL_REFLECTABLE_BODY_IMPL()

#define TEMPLATE_REFLECTABLE(type_template_header, ... /*reflectable_type_template*/) \
    EIGHTREFL_DEPAREN(type_template_header) struct xxeightrefl<__VA_ARGS__> { \
        using R = __VA_ARGS__; \
        using CleanR = typename ::xxeightrefl_dirty_traits<R>::R; \
        EIGHTREFL_REFLECTABLE_BODY_IMPL()

#define CONDITIONAL_REFLECTABLE(... /*reflectable_type_condition*/) \
    template <typename R> struct xxeightrefl<R, std::enable_if_t<__VA_ARGS__>> { \
        using CleanR = typename ::xxeightrefl_dirty_traits<R>::R; \
        EIGHTREFL_REFLECTABLE_BODY_IMPL()


#define REFLECTABLE_INIT() \
        } \
        inline static auto xxfixture = eightrefl::fixture_of<R>(); \
    };


template <typename ReflectableType, typename enable = void>
struct xxeightrefl;


namespace eightrefl
{

template <typename DirtyReflectableType>
void reflectable()
{
    static auto xxlock = false; if (xxlock) return;
    xxlock = true;

    auto xxinjectable = injectable_t{};
    ::xxeightrefl<DirtyReflectableType>::evaluate(xxinjectable);
}

template <typename ReflectableType>
ReflectableType&& reflectable(ReflectableType&& object)
{
    reflectable<std::decay_t<ReflectableType>>();
    return std::forward<ReflectableType>(object);
}


template <typename DirtyReflectableType>
bool fixture_of()
{
    static_assert
    (
        detail::is_complete<::xxeightrefl_traits<DirtyReflectableType>>::value,
        "fixture: reflection declaration for this type not found"
    );

    #ifdef EIGHTREFL_DISABLE_REFLECTION_FIXTURE
    return false;
    #else
    if constexpr (::xxeightrefl_traits_has_reflectable_lazy_evaluate<DirtyReflectableType>::value)
    {
        return false;
    }
    else
    {
        reflectable<DirtyReflectableType>();
        return true;
    }
    #endif // EIGHTREFL_DISABLE_REFLECTION_FIXTURE
}


template <typename DirtyReflectableType>
type_t* find_or_add_type()
{
    using dirty_reflectable_type = typename std::conditional_t
    <
        std::is_reference_v<DirtyReflectableType>,
        detail::to_reflectable_reference<DirtyReflectableType>,
        std::conditional_t
        <
            std::is_pointer_v<DirtyReflectableType>,
            detail::to_reflectable_pointer<DirtyReflectableType>,
            detail::to_reflectable_object<DirtyReflectableType>
        >
    >::type;

    using reflectable_type = typename ::xxeightrefl_dirty_traits<dirty_reflectable_type>::R;

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


template <typename ReflectableType, typename DirtyReflectableParentType>
parent_t* find_or_add_parent(type_t* type)
{
    using reflectable_parent_type = typename ::xxeightrefl_dirty_traits<DirtyReflectableParentType>::R;

    static_assert
    (
        std::is_base_of_v<reflectable_parent_type, ReflectableType>,
        "find_or_add_parent: ReflectableType must derive from ReflectableParentType"
    );

    auto xxname = name_of<DirtyReflectableParentType>();

    auto xxmeta = type->parent.find(xxname);
    if (xxmeta == nullptr)
    {
        auto xxtype = find_or_add_type<reflectable_parent_type>();
        xxmeta = type->parent.add
        (
            xxname,
            {
                .type = xxtype,
                .cast = handler_parent_cast<ReflectableType, reflectable_parent_type>()
            }
        );

        xxtype->child.add
        (
            type->name,
            {
                .type = type,
                .cast = handler_child_cast<reflectable_parent_type, ReflectableType>()
            }
        );
    }

    return xxmeta;
}

template <typename ReflectableType, typename DirtyReflectableParentType,
          class InjectionType>
parent_t* find_or_add_parent(type_t* type, InjectionType& injection)
{
    auto xxparent = find_or_add_parent<ReflectableType, DirtyReflectableParentType>(type);
    injection.template parent<ReflectableType, DirtyReflectableParentType>(*xxparent);

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
    using function_traits = ::xxeightrefl_function_traits<DirtyFactoryType>;
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
    using function_traits = ::xxeightrefl_function_traits<DirtyFactoryType>;

    auto xxfactory = find_or_add_factory<DirtyFactoryType>(type);
    injection.template factory<ReflectableType, typename function_traits::type_pointer>(*xxfactory);

    return xxfactory;
}


template <typename DirtyFunctionType = void, typename FunctionTypePointer>
function_t* find_or_add_function(type_t* type, std::string const& name, FunctionTypePointer pointer)
{
    using function_traits = ::xxeightrefl_function_traits
    <
        typename ::xxeightrefl_mark_dirty<FunctionTypePointer, DirtyFunctionType>::type
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
    using property_traits = ::xxeightrefl_property_traits
    <
        typename std::conditional_t
        <
            std::is_null_pointer_v<ITypePointer>,
            ::xxeightrefl_mark_dirty<OTypePointer, IODirtyType>,
            ::xxeightrefl_mark_dirty<ITypePointer, IODirtyType>
        >::type
    >;

    using dirty_type = typename property_traits::dirty_type;

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
                                 std::function<std::any(std::any const&)> ihandler,
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
                                 std::function<std::any(std::any const&)> ihandler,
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
    using deleter_traits = ::xxeightrefl_deleter_traits<DirtyDeleterType>;
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
    using deleter_traits = ::xxeightrefl_deleter_traits<DirtyDeleterType>;

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


template <typename ReflectionType, class InjectionType>
auto handler_injection_call()
{
    return [](std::any const& injectable_context)
    {
        ::xxeightrefl<ReflectionType>::evaluate(utility::forward<InjectionType&>(injectable_context));
    };
}

template <typename ReflectableType, class DirtyReflectableInjectionType>
injection_t* find_or_add_injection(type_t* type)
{
    using reflectable_injection_type = ::xxeightrefl_dirty_traits<DirtyReflectableInjectionType>::R;

    static_assert
    (
        std::is_base_of_v<injectable_t, reflectable_injection_type>,
        "find_or_add_injection: ReflectableInjectionType must derive from injectable_t"
    );

    auto xxtype = find_or_add_type<DirtyReflectableInjectionType>();

    auto xxmeta = type->injection.find(xxtype->name);
    if (xxmeta == nullptr) xxmeta = type->injection.add
    (
        xxtype->name,
        {
            .type = xxtype,
            .call = handler_injection_call<ReflectableType, reflectable_injection_type>()
        }
    );

    return xxmeta;
}

template <typename ReflectableType, class DirtyReflectableInjectionType,
          class InjectionType>
injection_t* find_or_add_injection(type_t* type, InjectionType& injection)
{
    auto xxinjection = find_or_add_injection<ReflectableType, DirtyReflectableInjectionType>(type);
    injection.template injection<ReflectableType, DirtyReflectableInjectionType>(*xxinjection);

    return xxinjection;
}

} // namespace eightrefl

#endif // EIGHTREFL_REFLECTABLE_HPP
