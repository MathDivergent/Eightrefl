#ifndef EIGHTREFL_TYPE_HPP
#define EIGHTREFL_TYPE_HPP

#include <cstddef> // size_t

#include <string> // string
#include <any> // any
#include <functional> // function

#include <Eightrefl/Attribute.hpp>

template <typename ReflectableType, typename enable = void>
struct xxeightrefl;

namespace eightrefl
{

struct registry_t;
struct injection_t;
struct child_t;

struct parent_t;
struct factory_t;
struct function_t;
struct property_t;
struct deleter_t;
struct meta_t;

struct EIGHTREFL_API type_t
{
    std::string const name;
    registry_t* const registry = nullptr;
    std::size_t const size = 0;
    std::function<std::any(std::any& object)> const context = nullptr;

    attribute_t<injection_t> injection;
    attribute_t<child_t> child;

    attribute_t<parent_t> parent;
    attribute_t<factory_t> factory;
    attribute_t<attribute_t<function_t>> function;
    attribute_t<property_t> property;
    attribute_t<deleter_t> deleter;
    attribute_t<meta_t> meta;
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
