#ifndef EIGHTREFL_REFLECTION_HPP
#define EIGHTREFL_REFLECTION_HPP

#include <string> // string

#include <Eightrefl/Attribute.hpp>

template <typename ReflectableType, typename enable = void>
struct xxeightrefl;

namespace eightrefl
{

struct parent_t;
struct factory_t;
struct function_t;
struct property_t;
struct deleter_t;
struct meta_t;

struct reflection_t
{
    std::string const name;

    attribute_t<parent_t> parent;
    attribute_t<factory_t> factory;
    attribute_t<attribute_t<function_t>> function;
    attribute_t<property_t> property;
    attribute_t<deleter_t> deleter;
    attribute_t<meta_t> meta;
};

} // namespace eightrefl

#endif // EIGHTREFL_REFLECTION_HPP
