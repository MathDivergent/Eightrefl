#ifndef EIGHTREFL_CHILD_HPP
#define EIGHTREFL_CHILD_HPP

#include <any> // any, any_cast
#include <functional> // function
#include <type_traits> // false_type, void_t, declval, true_type

namespace eightrefl
{

struct type_t;

struct EIGHTREFL_API child_t
{
    type_t* const type = nullptr;
    std::function<std::any(std::any const& parent_context)> const cast = nullptr;
};

namespace detail
{

template <typename FromType, typename ToType, typename enable = void>
struct is_static_castable : std::false_type {};

template <typename FromType, typename ToType>
struct is_static_castable<FromType, ToType, std::void_t<decltype( static_cast<ToType>(std::declval<FromType>()) )>> : std::true_type {};

} // namespace detail

template <typename ReflectableType, typename ChildReflectableType>
auto handler_child_cast()
{
    return [](std::any const& parent_context) -> std::any
    {
        auto xxparent_pointer = std::any_cast<ReflectableType*>(parent_context);
        if constexpr (detail::is_static_castable<ReflectableType*, ChildReflectableType*>::value)
        {
            return static_cast<ChildReflectableType*>(xxparent_pointer);
        }
        else
        {
            #ifdef EIGHTREFL_RTTI_ENABLE
            return dynamic_cast<ChildReflectableType*>(xxparent_pointer);
            #else
            return nullptr;
            #endif // EIGHTREFL_RTTI_ENABLE
        }
    };
}

} // namespace eightrefl

#endif // EIGHTREFL_CHILD_HPP