#ifndef EIGHTREFL_DETAIL_META_HPP
#define EIGHTREFL_DETAIL_META_HPP

#include <type_traits> // conjunction, disjunction, false_type, true_type, void_t, type_identity
#include <utility> // pair

template <typename ReflectableType, typename enable = void>
struct xxeightrefl_dirty { using R = ReflectableType; };

template <typename ReflectableType, typename enable = void>
struct xxeightrefl_traits;

template <typename ReflectableType, typename enable = void>
struct xxeightrefl;

template <typename, typename enable = void> struct xxeightrefl_traits_has_reflectable_name : std::false_type {};
template <typename ReflectableType>
struct xxeightrefl_traits_has_reflectable_name<ReflectableType, std::void_t<decltype(&::xxeightrefl_traits<ReflectableType>::name)>> : std::true_type {};

template <typename, typename enable = void> struct xxeightrefl_traits_has_reflectable_registry : std::false_type {};
template <typename ReflectableType>
struct xxeightrefl_traits_has_reflectable_registry<ReflectableType, std::void_t<decltype(&::xxeightrefl_traits<ReflectableType>::registry)>> : std::true_type {};

template <typename, typename enable = void> struct xxeightrefl_traits_has_reflectable_lazy_evaluate : std::false_type {};
template <typename ReflectableType>
struct xxeightrefl_traits_has_reflectable_lazy_evaluate<ReflectableType, std::void_t<typename ::xxeightrefl_traits<ReflectableType>::xxlazy_evaluate>> : std::true_type {};


namespace eightrefl
{

namespace meta
{

template <typename FromType, typename ToType, typename enable = void>
struct is_static_castable : std::false_type {};

template <typename FromType, typename ToType>
struct is_static_castable<FromType, ToType, std::void_t<decltype( static_cast<ToType>(std::declval<FromType>()) )>> : std::true_type {};

template <typename Type>
struct inherits : std::conditional_t
<
    std::conjunction_v< std::is_class<Type>, std::negation<std::is_final<Type>> >,
    Type,
    std::type_identity<Type>
> {};

template <typename ReferenceType>
struct to_reflectable_reference { using type = std::remove_const_t<std::remove_reference_t<ReferenceType>>*; };

template <typename PointerType>
struct to_reflectable_pointer { using type = std::remove_const_t<std::remove_pointer_t<PointerType>>*; };

template <typename ObjectType>
struct to_reflectable_object { using type = std::remove_const_t<ObjectType>; };

template <typename, typename enable = void> struct is_complete : std::false_type {};
template <typename Type> struct is_complete<Type, std::void_t<decltype(sizeof(Type))>> : std::true_type {};

template <typename MemberPointerType, typename DirtyMemberPointerType>
struct mark_dirty;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const, DirtyReturnType(DirtyArgumentTypes...) const>
{
    using type = DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...) const;
};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const&, DirtyReturnType(DirtyArgumentTypes...) const&>
{
    using type = DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...) const&;
};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...), DirtyReturnType(DirtyArgumentTypes...)>
{
    using type = DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...);
};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...)&, DirtyReturnType(DirtyArgumentTypes...)&>
{
    using type = DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...)&;
};

template <typename ReturnType, typename... ArgumentTypes,
          typename DirtyReturnType, typename... DirtyArgumentTypes>
struct mark_dirty<ReturnType(*)(ArgumentTypes...), DirtyReturnType(DirtyArgumentTypes...)>
{
    using type = DirtyReturnType(*)(DirtyArgumentTypes...);
};

template <typename ReflectableType, typename PropertyType, typename DirtyPropertyType>
struct mark_dirty<PropertyType ReflectableType::*, DirtyPropertyType>
{
    using type = DirtyPropertyType ReflectableType::*;
};

template <typename PropertyType, typename DirtyPropertyType>
struct mark_dirty<PropertyType*, DirtyPropertyType>
{
    using type = DirtyPropertyType*;
};

template <typename PropertyType>
struct property_traits;

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType(ReflectableType::*)(void) const> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType(ReflectableType::*)(void) const&> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType(ReflectableType::*)(void)> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType(ReflectableType::*)(void)&> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<void(ReflectableType::*)(PropertyType)> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<void(ReflectableType::*)(PropertyType)&> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<PropertyType(*)(void)> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<PropertyType() const> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<PropertyType()> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<void(PropertyType)> { using type = PropertyType; };

template <typename ReflectableType, typename PropertyType>
struct property_traits<PropertyType ReflectableType::*> { using type = PropertyType; };

template <typename PropertyType>
struct property_traits<PropertyType*> { using type = PropertyType; };

template <typename>
struct function_traits;

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ArgumentTypes...) const>
{
    using dirty_type = ReturnType(ArgumentTypes...) const;
    using dirty_type_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxeightrefl_dirty<ReturnType>::R(typename ::xxeightrefl_dirty<ArgumentTypes>::R...) const;
    using type_pointer = typename ::xxeightrefl_dirty<ReturnType>::R(*)(typename ::xxeightrefl_dirty<ArgumentTypes>::R...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ArgumentTypes...) const&>
{
    using dirty_type = ReturnType(ArgumentTypes...) const&;
    using dirty_type_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxeightrefl_dirty<ReturnType>::R(typename ::xxeightrefl_dirty<ArgumentTypes>::R...) const&;
    using type_pointer = typename ::xxeightrefl_dirty<ReturnType>::R(*)(typename ::xxeightrefl_dirty<ArgumentTypes>::R...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ArgumentTypes...)>
{
    using dirty_type = ReturnType(ArgumentTypes...);
    using dirty_type_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxeightrefl_dirty<ReturnType>::R(typename ::xxeightrefl_dirty<ArgumentTypes>::R...);
    using type_pointer = typename ::xxeightrefl_dirty<ReturnType>::R(*)(typename ::xxeightrefl_dirty<ArgumentTypes>::R...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ArgumentTypes...)&>
{
    using dirty_type = ReturnType(ArgumentTypes...)&;
    using dirty_type_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxeightrefl_dirty<ReturnType>::R(typename ::xxeightrefl_dirty<ArgumentTypes>::R...)&;
    using type_pointer = typename ::xxeightrefl_dirty<ReturnType>::R(*)(typename ::xxeightrefl_dirty<ArgumentTypes>::R...);
};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ClassType::*)(ArgumentTypes...) const>
    : function_traits<ReturnType(ArgumentTypes...) const> {};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ClassType::*)(ArgumentTypes...) const&>
    : function_traits<ReturnType(ArgumentTypes...) const&> {};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ClassType::*)(ArgumentTypes...)>
    : function_traits<ReturnType(ArgumentTypes...)> {};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(ClassType::*)(ArgumentTypes...)&>
    : function_traits<ReturnType(ArgumentTypes...)&> {};

template <typename ReturnType, typename... ArgumentTypes>
struct function_traits<ReturnType(*)(ArgumentTypes...)>
    : function_traits<ReturnType(ArgumentTypes...)> {};

template <typename>
struct deleter_traits;

template <typename ReturnType, typename ReflectableType>
struct deleter_traits<ReturnType(ReflectableType)>
{
    using dirty_type = ReturnType(ReflectableType);
    using dirty_type_pointer = ReturnType(*)(ReflectableType);

    using type = typename ::xxeightrefl_dirty<ReturnType>::R(typename ::xxeightrefl_dirty<ReflectableType>::R);
    using type_pointer = typename ::xxeightrefl_dirty<ReturnType>::R(*)(typename ::xxeightrefl_dirty<ReflectableType>::R);
};

template <typename ReturnType, typename ReflectableType>
struct deleter_traits<ReturnType(*)(ReflectableType)>
    : deleter_traits<ReturnType(ReflectableType)> {};

namespace detail
{

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(ParentReflectableType::* function)(ArgumentTypes...) const)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ParentReflectableType::* function)(ArgumentTypes...) const)
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...) const>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(ParentReflectableType::* function)(ArgumentTypes...) const&)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ParentReflectableType::* function)(ArgumentTypes...) const&)
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...) const&>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(ParentReflectableType::* function)(ArgumentTypes...))
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ParentReflectableType::* function)(ArgumentTypes...))
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...)>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ParentReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(ParentReflectableType::* function)(ArgumentTypes...)&)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ParentReflectableType::* function)(ArgumentTypes...)&)
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...)&>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr_impl(ReturnType(* function)(ArgumentTypes...))
{
    return function;
}

template <typename ReflectableType, typename ParentReflectableType, typename ValueType>
constexpr auto property_ptr_impl(ValueType ParentReflectableType::* property)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ValueType ParentReflectableType::* property)
        {
            return static_cast<ValueType ReflectableType::*>(property);
        }
    };
    return xxinner::get(property);
}

} // namespace detail

template <typename...>
struct access_traits;

template <>
struct access_traits<>
{
    template <typename...>
    struct property
    {
        template <typename PropertyType>
        static constexpr auto of(PropertyType(* iproperty)(void), void(* oproperty)(PropertyType))
        {
            return std::make_pair(iproperty, oproperty);
        }

        template <typename PropertyType>
        static constexpr auto of(PropertyType* iproperty, PropertyType* oproperty)
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename PropertyType>
    struct property<PropertyType()>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty<PropertyType>::R(* iproperty)(void), void(* oproperty)(typename ::xxeightrefl_dirty<PropertyType>::R))
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename IPropertyType, typename OPropertyType>
    struct property<IPropertyType(), void(OPropertyType)>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty<IPropertyType>::R(* iproperty)(void), void(* oproperty)(typename ::xxeightrefl_dirty<OPropertyType>::R))
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename PropertyType>
    struct property<PropertyType>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty<PropertyType>::R* iproperty, typename ::xxeightrefl_dirty<PropertyType>::R* oproperty)
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename...>
    struct function
    {
        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(* function)(ArgumentTypes...)) { return function; }
    };

    template <typename ReturnType, typename... ArgumentTypes>
    struct function<ReturnType(ArgumentTypes...)>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty<ReturnType>::R(* function)(typename ::xxeightrefl_dirty<ArgumentTypes>::R...)) { return function; }

        template <typename OtherReturnType, typename... OtherArgumentTypes>
        static constexpr auto of(OtherReturnType(* function)(OtherArgumentTypes...)) { return function; }
    };
};

template <class ClassType>
struct access_traits<ClassType>
{
    template <typename ITypePointer, typename OTypePointer>
    static constexpr auto property_data(ITypePointer iproperty, OTypePointer oproperty)
    {
        return std::make_pair(detail::property_ptr_impl<ClassType>(iproperty), detail::property_ptr_impl<ClassType>(oproperty));
    }

    template <typename ITypePointer, typename OTypePointer>
    static constexpr auto function_data(ITypePointer iproperty, OTypePointer oproperty)
    {
        return std::make_pair(detail::function_ptr_impl<ClassType>(iproperty), detail::function_ptr_impl<ClassType>(oproperty));
    }

    template <typename ITypePointer>
    static constexpr auto function_data(ITypePointer iproperty, std::nullptr_t)
    {
        return std::make_pair(detail::function_ptr_impl<ClassType>(iproperty), nullptr);
    }

    template <typename FunctionTypePointer>
    static constexpr auto function_data(FunctionTypePointer function)
    {
        return detail::function_ptr_impl<ClassType>(function);
    }

    template <typename...>
    struct property
    {
        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType ParentClassType::* iproperty, PropertyType ParentClassType::* oproperty)
        {
            return property_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename PropertyType>
        static constexpr auto of(PropertyType(* iproperty)(void), void(* oproperty)(PropertyType)) { return std::make_pair(iproperty, oproperty); }

        template <typename PropertyType>
        static constexpr auto of(PropertyType* iproperty, PropertyType* oproperty) { return std::make_pair(iproperty, oproperty); }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType() const>
    {
        using PropertyType = typename ::xxeightrefl_dirty<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, std::type_identity_t<PropertyType(ParentClassType::*)(void) const>)
        {
            return function_data(iproperty, nullptr);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType() const, void(ODirtyPropertyType)>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty<ODirtyPropertyType>::R))
        {
            return function_data(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType() const, void(ODirtyPropertyType)&>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty<ODirtyPropertyType>::R)&)
        {
            return function_data(iproperty, oproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType() const&>
    {
        using PropertyType = typename ::xxeightrefl_dirty<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, std::type_identity_t<PropertyType(ParentClassType::*)(void) const&>)
        {
            return function_data(iproperty, nullptr);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType() const&, void(ODirtyPropertyType)>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty<ODirtyPropertyType>::R))
        {
            return function_data(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType() const&, void(ODirtyPropertyType)&>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty<ODirtyPropertyType>::R)&)
        {
            return function_data(iproperty, oproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType()>
    {
        using PropertyType = typename ::xxeightrefl_dirty<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), std::type_identity_t<PropertyType(ParentClassType::*)(void)>)
        {
            return function_data(iproperty, nullptr);
        }

        static constexpr auto of(PropertyType(* iproperty)(void), void(* oproperty)(PropertyType))
        {
            return std::make_pair(iproperty, oproperty);
        }

        static constexpr auto of(PropertyType(* iproperty)(void), std::type_identity_t<PropertyType(*)(void)>)
        {
            return std::make_pair(iproperty, nullptr);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType(), void(ODirtyPropertyType)>
    {
        using IPropertyType = typename ::xxeightrefl_dirty<IDirtyPropertyType>::R;
        using OPropertyType = typename ::xxeightrefl_dirty<ODirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(IPropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(OPropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        static constexpr auto of(IPropertyType(* iproperty)(void), void(* oproperty)(OPropertyType))
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType(), void(ODirtyPropertyType)&>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty<ODirtyPropertyType>::R)&)
        {
            return function_data(iproperty, oproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType()&>
    {
        using PropertyType = typename ::xxeightrefl_dirty<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return function_data(iproperty, oproperty);
        }

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, std::type_identity_t<PropertyType(ParentClassType::*)(void)&>)
        {
            return function_data(iproperty, nullptr);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType()&, void(ODirtyPropertyType)>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty<ODirtyPropertyType>::R))
        {
            return function_data(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType()&, void(ODirtyPropertyType)&>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty<ODirtyPropertyType>::R)&)
        {
            return function_data(iproperty, oproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType>
    {
        using PropertyType = typename ::xxeightrefl_dirty<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType ParentClassType::* iproperty, PropertyType ParentClassType::* oproperty)
        {
            return property_data(iproperty, oproperty);
        }

        static constexpr auto of(PropertyType* iproperty, PropertyType* oproperty) { return std::make_pair(iproperty, oproperty); }
    };

    template <typename...>
    struct function
    {
        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...) const) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...) const) { return function_data(function); }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...) const&) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...) const&) { return function_data(function); }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...)) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...)) { return function_data(function); }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...)&) { return function; }
        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...)&) { return function_data(function); }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(* function)(ArgumentTypes...)) { return function; }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...) const>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty<DirtyReturnType>::R(ClassType::* function)(typename ::xxeightrefl_dirty<DirtyArgumentTypes>::R...) const) { return function; }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxeightrefl_dirty<DirtyArgumentTypes>::R...) const)
        {
            return function_data(function);
        }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...) const&>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty<DirtyReturnType>::R(ClassType::* function)(typename ::xxeightrefl_dirty<DirtyArgumentTypes>::R...) const&) { return function; }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxeightrefl_dirty<DirtyArgumentTypes>::R...) const&)
        {
            return function_data(function);
        }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...)>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty<DirtyReturnType>::R(ClassType::* function)(typename ::xxeightrefl_dirty<DirtyArgumentTypes>::R...)) { return function; }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxeightrefl_dirty<DirtyArgumentTypes>::R...))
        {
            return function_data(function);
        }

        static constexpr auto of(typename ::xxeightrefl_dirty<DirtyReturnType>::R(* function)(typename ::xxeightrefl_dirty<DirtyArgumentTypes>::R...)) { return function; }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...)&>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty<DirtyReturnType>::R(ClassType::* function)(typename ::xxeightrefl_dirty<DirtyArgumentTypes>::R...)&) { return function; }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxeightrefl_dirty<DirtyArgumentTypes>::R...)&)
        {
            return function_data(function);
        }
    };
};

} // namespace meta

} // namespace eightrefl

#endif // EIGHTREFL_DETAIL_META_HPP
