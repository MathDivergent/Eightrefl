#ifndef EIGHTREFL_TRAITS_ACCESS_HPP
#define EIGHTREFL_TRAITS_ACCESS_HPP

#include <utility> // pair

#include <Eightrefl/Traits/Dirty.hpp>

namespace eightrefl
{

namespace detail
{

template <typename ReflectableType, typename ReflectableParentType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr(ReturnType(ReflectableParentType::* function)(ArgumentTypes...) const)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ReflectableParentType::* function)(ArgumentTypes...) const)
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...) const>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ReflectableParentType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr(ReturnType(ReflectableParentType::* function)(ArgumentTypes...) const&)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ReflectableParentType::* function)(ArgumentTypes...) const&)
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...) const&>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ReflectableParentType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr(ReturnType(ReflectableParentType::* function)(ArgumentTypes...))
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ReflectableParentType::* function)(ArgumentTypes...))
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...)>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ReflectableParentType, typename ReturnType, typename... ArgumentTypes>
constexpr auto function_ptr(ReturnType(ReflectableParentType::* function)(ArgumentTypes...)&)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ReturnType(ReflectableParentType::* function)(ArgumentTypes...)&)
        {
            return static_cast<ReturnType(ReflectableType::*)(ArgumentTypes...)&>(function);
        }
    };
    return xxinner::get(function);
}

template <typename ReflectableType, typename ReflectableParentType, typename ValueType>
constexpr auto property_ptr(ValueType ReflectableParentType::* property)
{
    struct xxinner : protected ReflectableType
    {
        static constexpr auto get(ValueType ReflectableParentType::* property)
        {
            return static_cast<ValueType ReflectableType::*>(property);
        }
    };
    return xxinner::get(property);
}

template <typename ReflectableType, typename ITypePointer, typename OTypePointer>
static constexpr auto property_ptr(ITypePointer iproperty, OTypePointer oproperty)
{
    return std::make_pair(property_ptr<ReflectableType>(iproperty), property_ptr<ReflectableType>(oproperty));
}

template <typename ReflectableType, typename ITypePointer, typename OTypePointer>
static constexpr auto function_ptr(ITypePointer iproperty, OTypePointer oproperty)
{
    return std::make_pair(function_ptr<ReflectableType>(iproperty), function_ptr<ReflectableType>(oproperty));
}

} // namespace detail

} // namespace eightrefl


template <typename...>
struct xxeightrefl_access_traits;

template <>
struct xxeightrefl_access_traits<>
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

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType()>
    {
        using PropertyType = typename ::xxeightrefl_dirty_traits<DirtyPropertyType>::R;

        static constexpr auto of(PropertyType(* iproperty)(void), std::type_identity_t<PropertyType(*)(void)>)
        {
            return std::make_pair(iproperty, nullptr);
        }
    };

    template <typename DirtyPropertyType>
    struct property<void(DirtyPropertyType)>
    {
        using PropertyType = typename ::xxeightrefl_dirty_traits<DirtyPropertyType>::R;

        static constexpr auto of(std::type_identity_t<void(*)(PropertyType)>, void(* oproperty)(PropertyType))
        {
            return std::make_pair(nullptr, oproperty);
        }
    };

    template <typename IPropertyType, typename OPropertyType>
    struct property<IPropertyType(), void(OPropertyType)>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<IPropertyType>::R(* iproperty)(void), void(* oproperty)(typename ::xxeightrefl_dirty_traits<OPropertyType>::R))
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename PropertyType>
    struct property<PropertyType>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<PropertyType>::R* iproperty, typename ::xxeightrefl_dirty_traits<PropertyType>::R* oproperty)
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename...>
    struct function
    {
        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(* function)(ArgumentTypes...))
        {
            return function;
        }
    };

    template <typename ReturnType, typename... ArgumentTypes>
    struct function<ReturnType(ArgumentTypes...)>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<ReturnType>::R(* function)(typename ::xxeightrefl_dirty_traits<ArgumentTypes>::R...))
        {
            return function;
        }

        template <typename OtherReturnType, typename... OtherArgumentTypes>
        static constexpr auto of(OtherReturnType(* function)(OtherArgumentTypes...))
        {
            return function;
        }
    };
};

template <class ClassType>
struct xxeightrefl_access_traits<ClassType>
{
    template <typename...>
    struct property
    {
        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType ParentClassType::* iproperty, PropertyType ParentClassType::* oproperty)
        {
            return eightrefl::detail::property_ptr<ClassType>(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType))
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType))
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType))
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }

        template <typename ParentClassType, typename PropertyType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }

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

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType() const>
    {
        using PropertyType = typename ::xxeightrefl_dirty_traits<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const, std::type_identity_t<PropertyType(ParentClassType::*)(void) const>)
        {
            return std::make_pair(eightrefl::detail::function_ptr<ClassType>(iproperty), nullptr);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType() const&>
    {
        using PropertyType = typename ::xxeightrefl_dirty_traits<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void) const&, std::type_identity_t<PropertyType(ParentClassType::*)(void) const&>)
        {
            return std::make_pair(eightrefl::detail::function_ptr<ClassType>(iproperty), nullptr);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType()>
    {
        using PropertyType = typename ::xxeightrefl_dirty_traits<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void), std::type_identity_t<PropertyType(ParentClassType::*)(void)>)
        {
            return std::make_pair(eightrefl::detail::function_ptr<ClassType>(iproperty), nullptr);
        }

        static constexpr auto of(PropertyType(* iproperty)(void), std::type_identity_t<PropertyType(*)(void)>)
        {
            return std::make_pair(iproperty, nullptr);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType()&>
    {
        using PropertyType = typename ::xxeightrefl_dirty_traits<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType(ParentClassType::* iproperty)(void)&, std::type_identity_t<PropertyType(ParentClassType::*)(void)&>)
        {
            return std::make_pair(eightrefl::detail::function_ptr<ClassType>(iproperty), nullptr);
        }
    };

    template <typename DirtyPropertyType>
    struct property<void(DirtyPropertyType)>
    {
        using PropertyType = typename ::xxeightrefl_dirty_traits<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(std::type_identity_t<void(ParentClassType::*)(PropertyType)>, void(ParentClassType::* oproperty)(PropertyType))
        {
            return std::make_pair(nullptr, eightrefl::detail::function_ptr<ClassType>(oproperty));
        }

        static constexpr auto of(std::type_identity_t<void(*)(PropertyType)>, void(* oproperty)(PropertyType))
        {
            return std::make_pair(nullptr, oproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<void(DirtyPropertyType)&>
    {
        using PropertyType = typename ::xxeightrefl_dirty_traits<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(std::type_identity_t<void(ParentClassType::* )(PropertyType)&>, void(ParentClassType::* oproperty)(PropertyType)&)
        {
            return std::make_pair(nullptr, eightrefl::detail::function_ptr<ClassType>(oproperty));
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType() const, void(ODirtyPropertyType)>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty_traits<ODirtyPropertyType>::R))
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType() const, void(ODirtyPropertyType)&>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void) const, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty_traits<ODirtyPropertyType>::R)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType() const&, void(ODirtyPropertyType)>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty_traits<ODirtyPropertyType>::R))
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType() const&, void(ODirtyPropertyType)&>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void) const&, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty_traits<ODirtyPropertyType>::R)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType(), void(ODirtyPropertyType)>
    {
        using IPropertyType = typename ::xxeightrefl_dirty_traits<IDirtyPropertyType>::R;
        using OPropertyType = typename ::xxeightrefl_dirty_traits<ODirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(IPropertyType(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(OPropertyType))
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
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
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void), void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty_traits<ODirtyPropertyType>::R)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType()&, void(ODirtyPropertyType)>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty_traits<ODirtyPropertyType>::R))
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }
    };

    template <typename IDirtyPropertyType, typename ODirtyPropertyType>
    struct property<IDirtyPropertyType()&, void(ODirtyPropertyType)&>
    {
        template <typename ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<IDirtyPropertyType>::R(ParentClassType::* iproperty)(void)&, void(ParentClassType::* oproperty)(typename ::xxeightrefl_dirty_traits<ODirtyPropertyType>::R)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(iproperty, oproperty);
        }
    };

    template <typename DirtyPropertyType>
    struct property<DirtyPropertyType>
    {
        using PropertyType = typename ::xxeightrefl_dirty_traits<DirtyPropertyType>::R;

        template <typename ParentClassType>
        static constexpr auto of(PropertyType ParentClassType::* iproperty, PropertyType ParentClassType::* oproperty)
        {
            return eightrefl::detail::property_ptr<ClassType>(iproperty, oproperty);
        }

        static constexpr auto of(PropertyType* iproperty, PropertyType* oproperty)
        {
            return std::make_pair(iproperty, oproperty);
        }
    };

    template <typename...>
    struct function
    {
        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...) const)
        {
            return function;
        }

        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...) const)
        {
            return eightrefl::detail::function_ptr<ClassType>(function);
        }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...) const&)
        {
            return function;
        }

        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...) const&)
        {
            return eightrefl::detail::function_ptr<ClassType>(function);
        }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...))
        {
            return function;
        }

        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...))
        {
            return eightrefl::detail::function_ptr<ClassType>(function);
        }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ClassType::* function)(ArgumentTypes...)&)
        {
            return function;
        }

        template <class ParentClassType, typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(ParentClassType::* function)(ArgumentTypes...)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(function);
        }

        template <typename ReturnType, typename... ArgumentTypes>
        static constexpr auto of(ReturnType(* function)(ArgumentTypes...))
        {
            return function;
        }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...) const>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<DirtyReturnType>::R(ClassType::* function)(typename ::xxeightrefl_dirty_traits<DirtyArgumentTypes>::R...) const)
        {
            return function;
        }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxeightrefl_dirty_traits<DirtyArgumentTypes>::R...) const)
        {
            return eightrefl::detail::function_ptr<ClassType>(function);
        }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...) const&>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<DirtyReturnType>::R(ClassType::* function)(typename ::xxeightrefl_dirty_traits<DirtyArgumentTypes>::R...) const&)
        {
            return function;
        }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxeightrefl_dirty_traits<DirtyArgumentTypes>::R...) const&)
        {
            return eightrefl::detail::function_ptr<ClassType>(function);
        }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...)>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<DirtyReturnType>::R(ClassType::* function)(typename ::xxeightrefl_dirty_traits<DirtyArgumentTypes>::R...))
        {
            return function;
        }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxeightrefl_dirty_traits<DirtyArgumentTypes>::R...))
        {
            return eightrefl::detail::function_ptr<ClassType>(function);
        }

        static constexpr auto of(typename ::xxeightrefl_dirty_traits<DirtyReturnType>::R(* function)(typename ::xxeightrefl_dirty_traits<DirtyArgumentTypes>::R...))
        {
            return function;
        }
    };

    template <typename DirtyReturnType, typename... DirtyArgumentTypes>
    struct function<DirtyReturnType(DirtyArgumentTypes...)&>
    {
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<DirtyReturnType>::R(ClassType::* function)(typename ::xxeightrefl_dirty_traits<DirtyArgumentTypes>::R...)&)
        {
            return function;
        }

        template <class ParentClassType>
        static constexpr auto of(typename ::xxeightrefl_dirty_traits<DirtyReturnType>::R(ParentClassType::* function)(typename ::xxeightrefl_dirty_traits<DirtyArgumentTypes>::R...)&)
        {
            return eightrefl::detail::function_ptr<ClassType>(function);
        }
    };
};

#endif // EIGHTREFL_TRAITS_ACCESS_HPP
