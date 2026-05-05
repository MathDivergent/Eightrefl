#ifndef EIGHTREFL_PARENT_HPP
#define EIGHTREFL_PARENT_HPP

#include <any> // any, any_cast
#include <functional> // function

#include <Eightrefl/Attribute.hpp>
#include <Eightrefl/Meta.hpp>

#define PARENT(... /*reflectable_parent_type*/) \
    { \
        auto xxparent = eightrefl::find_or_add_parent<CleanR, __VA_ARGS__>(xxtype, injection); \
        xxmeta = &xxparent->meta; \
    }

namespace eightrefl
{

struct type_t;

struct EIGHTREFL_API parent_t
{
    type_t* const type = nullptr;
    std::function<std::any(std::any const& child_context)> const cast = nullptr;
    attribute_t<meta_t> meta{};
};

template <typename ReflectableType, typename ReflectableParentType>
auto handler_parent_cast()
{
    return [](std::any const& child_context) -> std::any
    {
        return static_cast<ReflectableParentType*>(std::any_cast<ReflectableType*>(child_context));
    };
}

} // namespace eightrefl

#endif // EIGHTREFL_PARENT_HPP
