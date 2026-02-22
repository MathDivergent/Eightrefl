#ifndef EIGHTREFL_PARENT_HPP
#define EIGHTREFL_PARENT_HPP

#include <any> // any
#include <functional> // function

#include <Eightrefl/Attribute.hpp>

#include <Eightrefl/Detail/Meta.hpp>

// .parent<R, reflectable_type>()
#define PARENT(... /*reflectable_type*/) \
    { \
        auto xxparent = eightrefl::find_or_add_parent<CleanR, __VA_ARGS__>(xxtype); \
        injection.template parent<CleanR, __VA_ARGS__>(*xxparent); \
        xxmeta = &xxparent->meta; \
    }

namespace eightrefl
{

struct type_t;
struct meta_t;

struct EIGHTREFL_API parent_t
{
    type_t* const type = nullptr;
    std::function<std::any(std::any const& child_context)> const cast = nullptr;
    attribute_t<meta_t> meta{};
};

template <typename ReflectableType, typename ParentReflectableType>
auto handler_parent_cast()
{
    return [](std::any const& child_context) -> std::any
    {
        return static_cast<ParentReflectableType*>(std::any_cast<ReflectableType*>(child_context));
    };
}

} // namespace eightrefl

#endif // EIGHTREFL_PARENT_HPP
