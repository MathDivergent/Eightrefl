#ifndef EIGHTREFL_TRAITS_DIRTY_HPP
#define EIGHTREFL_TRAITS_DIRTY_HPP

#include <type_traits> // conjunction, is_class, negation, is_final, type_identity

template <typename ReflectableType, typename enable = void>
struct xxeightrefl_dirty_traits
{
    using R = ReflectableType;
};


template <typename ReflectableType>
struct xxeightrefl_enable_dirty : std::conditional_t
<
    std::conjunction_v
    <
        std::is_class<ReflectableType>,
        std::negation<std::is_final<ReflectableType>>
    >,
    ReflectableType,
    std::type_identity<ReflectableType>
> {};


template <typename MemberPointerType, typename DirtyMemberPointerType = void>
struct xxeightrefl_mark_dirty;

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const> : std::type_identity<ReturnType(ReflectableType::*)(ArgumentTypes...) const> {};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const, DirtyReturnType(DirtyArgumentTypes...) const> : std::type_identity<DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...) const> {};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const&> : std::type_identity<ReturnType(ReflectableType::*)(ArgumentTypes...) const&> {};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...) const&, DirtyReturnType(DirtyArgumentTypes...) const&> : std::type_identity<DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...) const&> {};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...)> : std::type_identity<ReturnType(ReflectableType::*)(ArgumentTypes...)> {};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...), DirtyReturnType(DirtyArgumentTypes...)> : std::type_identity<DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...)> {};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...)&> : std::type_identity<ReturnType(ReflectableType::*)(ArgumentTypes...)&> {};

template <typename ReflectableType, typename ReturnType, typename... ArgumentTypes,
                                    typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(ReflectableType::*)(ArgumentTypes...)&, DirtyReturnType(DirtyArgumentTypes...)&> : std::type_identity<DirtyReturnType(ReflectableType::*)(DirtyArgumentTypes...)&> {};

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(*)(ArgumentTypes...)> : std::type_identity<ReturnType(*)(ArgumentTypes...)> {};

template <typename ReturnType, typename... ArgumentTypes,
          typename DirtyReturnType, typename... DirtyArgumentTypes>
struct xxeightrefl_mark_dirty<ReturnType(*)(ArgumentTypes...), DirtyReturnType(DirtyArgumentTypes...)> : std::type_identity<DirtyReturnType(*)(DirtyArgumentTypes...)> {};

template <typename ReflectableType, typename PropertyType>
struct xxeightrefl_mark_dirty<PropertyType ReflectableType::*> : std::type_identity<PropertyType ReflectableType::*> {};

template <typename ReflectableType, typename PropertyType, typename DirtyPropertyType>
struct xxeightrefl_mark_dirty<PropertyType ReflectableType::*, DirtyPropertyType> : std::type_identity<DirtyPropertyType ReflectableType::*> {};

template <typename PropertyType>
struct xxeightrefl_mark_dirty<PropertyType*> : std::type_identity<PropertyType*> {};

template <typename PropertyType, typename DirtyPropertyType>
struct xxeightrefl_mark_dirty<PropertyType*, DirtyPropertyType> : std::type_identity<DirtyPropertyType*> {};


#endif // EIGHTREFL_TRAITS_DIRTY_HPP
