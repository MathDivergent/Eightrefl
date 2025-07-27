#ifndef EIGHTREFL_CHILD_HPP
#define EIGHTREFL_CHILD_HPP

#include <any> // any
#include <functional> // function

#include <Eightrefl/Detail/Meta.hpp>

namespace eightrefl
{

struct type_t;

struct EIGHTREFL_API child_t
{
    type_t* const type = nullptr;
    std::function<std::any(std::any const& parent_context)> const cast = nullptr;
};

template <typename ReflectableType, typename ChildReflectableType>
auto handler_child_cast()
{
    return [](std::any const& parent_context) -> std::any
    {
        auto xxparent_pointer = std::any_cast<ReflectableType*>(parent_context);
        if constexpr (meta::is_static_castable<ReflectableType*, ChildReflectableType*>::value)
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