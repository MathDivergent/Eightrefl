#ifndef EIGHTREFL_TYPE_HPP
#define EIGHTREFL_TYPE_HPP

#include <cstddef> // size_t

#include <string> // string
#include <any> // any
#include <functional> // function

#include <Eightrefl/Attribute.hpp>

namespace eightrefl
{

struct reflection_t;
struct registry_t;
struct injection_t;

struct type_t
{
    std::string const name;
    reflection_t* const reflection = nullptr;
    registry_t* const registry = nullptr;
    std::size_t const size = 0;
    std::function<std::any(std::any& object)> const context = nullptr;

    attribute_t<injection_t> injection;
};

template <typename ReflectableType>
auto handler_type_context()
{
    return [](std::any& object)
    {
        return std::addressof(std::any_cast<ReflectableType&>(object));
    };
}

template <> inline auto handler_type_context<std::any>()
{
    return [](std::any& object)
    {
        return std::addressof(object);
    };
}

template <> inline auto handler_type_context<void>()
{
    return nullptr;
}

template <typename ReflectableType>
auto type_size()
{
    return sizeof(ReflectableType);
}

template <> inline auto type_size<void>()
{
    return std::size_t(0);
}

} // namespace eightrefl

#endif // EIGHTREFL_TYPE_HPP
