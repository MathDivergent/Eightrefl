#ifndef EIGHTREFL_PARENT_HPP
#define EIGHTREFL_PARENT_HPP

#include <string> // string
#include <any> // any
#include <functional> // function

#include <Eightrefl/Attribute.hpp>

#include <Eightrefl/Detail/Meta.hpp>

// .parent<R, reflectable_type>()
#define PARENT(... /*reflectable_type*/) \
    { \
        auto xxparent = eightrefl::find_or_add_parent<CleanR, __VA_ARGS__>(xxreflection); \
        injection.template parent<CleanR, __VA_ARGS__>(*xxparent); \
        xxmeta = &xxparent->meta; \
    }

namespace eightrefl
{

struct type_t;
struct meta_t;

struct EIGHTREFL_API parent_t
{
    std::string const name;
    type_t* const type = nullptr;
    std::function<std::any(std::any const& child_context)> const cast = nullptr;
    attribute_t<meta_t> meta;
};

template <typename ReflectableType, typename ParentReflectableType>
auto handler_parent_cast()
{
    return [](std::any const& child_context) -> std::any
    {
        auto xxchild_pointer = std::any_cast<ReflectableType*>(child_context);
        if constexpr (meta::is_static_castable<ParentReflectableType*, ReflectableType*>::value)
        {
            return static_cast<ParentReflectableType*>(xxchild_pointer);
        }
        else
        {
            #ifdef EIGHTREFL_RTTI_ENABLE
            return dynamic_cast<ParentReflectableType*>(xxchild_pointer);
            #else
            return nullptr;
            #endif // EIGHTREFL_RTTI_ENABLE
        }
    };
}

} // namespace eightrefl

#endif // EIGHTREFL_PARENT_HPP
