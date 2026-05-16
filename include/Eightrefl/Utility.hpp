#ifndef EIGHTREFL_UTILITY_HPP
#define EIGHTREFL_UTILITY_HPP

#include <any> // any
#include <memory> // addressof
#include <type_traits> // add_pointer, remove_const_t, remove_reference_t, remove_pointer_t, remove_const, is_reference, is_pointer

namespace eightrefl
{

namespace detail
{

template <typename ReferenceType>
struct to_reflectable_reference : std::add_pointer<std::remove_const_t<std::remove_reference_t<ReferenceType>>> {};

template <typename PointerType>
struct to_reflectable_pointer : std::add_pointer<std::remove_const_t<std::remove_pointer_t<PointerType>>> {};

template <typename ObjectType>
struct to_reflectable_object : std::remove_const<ObjectType> {};

} // namespace detail

inline namespace utility
{

template <typename ValueType>
std::any backward(ValueType&& result)
{
    if constexpr (std::is_reference_v<ValueType>)
    {
        return const_cast<typename detail::to_reflectable_reference<ValueType>::type>(std::addressof(result));
    }
    else if constexpr (std::is_pointer_v<ValueType>)
    {
        return const_cast<typename detail::to_reflectable_pointer<ValueType>::type>(result);
    }
    else
    {
        return result;
    }
}

template <typename ValueType>
ValueType forward(std::any const& object)
{
    if constexpr (std::is_reference_v<ValueType>)
    {
        return *std::any_cast<typename detail::to_reflectable_reference<ValueType>::type>(object);
    }
    else if constexpr (std::is_pointer_v<ValueType>)
    {
        return std::any_cast<typename detail::to_reflectable_pointer<ValueType>::type>(object);
    }
    else
    {
        return std::any_cast<typename detail::to_reflectable_object<ValueType>::type const&>(object);
    }
}

} // inline namespace utility

} // namespace eightrefl

#endif // EIGHTREFL_UTILITY_HPP
