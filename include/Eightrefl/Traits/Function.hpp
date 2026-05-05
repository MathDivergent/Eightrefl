#ifndef EIGHTREFL_TRAITS_FUNCTION_HPP
#define EIGHTREFL_TRAITS_FUNCTION_HPP

#include <Eightrefl/Traits/Dirty.hpp>

template <typename>
struct xxeightrefl_function_traits;

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ArgumentTypes...) const>
{
    using dirty_type = ReturnType(ArgumentTypes...) const;
    using dirty_type_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxeightrefl_dirty_traits<ReturnType>::R(typename ::xxeightrefl_dirty_traits<ArgumentTypes>::R...) const;
    using type_pointer = typename ::xxeightrefl_dirty_traits<ReturnType>::R(*)(typename ::xxeightrefl_dirty_traits<ArgumentTypes>::R...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ArgumentTypes...) const&>
{
    using dirty_type = ReturnType(ArgumentTypes...) const&;
    using dirty_type_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxeightrefl_dirty_traits<ReturnType>::R(typename ::xxeightrefl_dirty_traits<ArgumentTypes>::R...) const&;
    using type_pointer = typename ::xxeightrefl_dirty_traits<ReturnType>::R(*)(typename ::xxeightrefl_dirty_traits<ArgumentTypes>::R...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ArgumentTypes...)>
{
    using dirty_type = ReturnType(ArgumentTypes...);
    using dirty_type_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxeightrefl_dirty_traits<ReturnType>::R(typename ::xxeightrefl_dirty_traits<ArgumentTypes>::R...);
    using type_pointer = typename ::xxeightrefl_dirty_traits<ReturnType>::R(*)(typename ::xxeightrefl_dirty_traits<ArgumentTypes>::R...);
};

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ArgumentTypes...)&>
{
    using dirty_type = ReturnType(ArgumentTypes...)&;
    using dirty_type_pointer = ReturnType(*)(ArgumentTypes...);

    using type = typename ::xxeightrefl_dirty_traits<ReturnType>::R(typename ::xxeightrefl_dirty_traits<ArgumentTypes>::R...)&;
    using type_pointer = typename ::xxeightrefl_dirty_traits<ReturnType>::R(*)(typename ::xxeightrefl_dirty_traits<ArgumentTypes>::R...);
};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ClassType::*)(ArgumentTypes...) const> : xxeightrefl_function_traits<ReturnType(ArgumentTypes...) const> {};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ClassType::*)(ArgumentTypes...) const&> : xxeightrefl_function_traits<ReturnType(ArgumentTypes...) const&> {};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ClassType::*)(ArgumentTypes...)> : xxeightrefl_function_traits<ReturnType(ArgumentTypes...)> {};

template <class ClassType, typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(ClassType::*)(ArgumentTypes...)&> : xxeightrefl_function_traits<ReturnType(ArgumentTypes...)&> {};

template <typename ReturnType, typename... ArgumentTypes>
struct xxeightrefl_function_traits<ReturnType(*)(ArgumentTypes...)> : xxeightrefl_function_traits<ReturnType(ArgumentTypes...)> {};

#endif // EIGHTREFL_TRAITS_FUNCTION_HPP
