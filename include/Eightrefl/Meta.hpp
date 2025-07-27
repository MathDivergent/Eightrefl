#ifndef EIGHTREFL_META_HPP
#define EIGHTREFL_META_HPP

#include <string> // string
#include <any> // any

#include <Eightrefl/Attribute.hpp>

#include <Eightrefl/Detail/Meta.hpp>
#include <Eightrefl/Detail/Macro.hpp> // EIGHTREFL_DEPAREN

// .meta(external_name, meta_expression)
#define CUSTOM_META(touch_expression, meta_pointer, external_name, ... /*meta_expression*/) \
    { \
        auto xxitem = meta_pointer->find(external_name); \
        if (xxitem == nullptr) xxitem = meta_pointer->add(external_name, { external_name, std::any(__VA_ARGS__) }); \
        injection.template meta<CleanR, decltype(::eightrefl::meta::decltype_value(__VA_ARGS__))>(*xxitem); \
        EIGHTREFL_DEPAREN(touch_expression); \
    }

#define META(external_name, ... /*meta_expression*/) CUSTOM_META((xxsubmeta = &xxitem->meta), xxmeta, external_name, __VA_ARGS__)
#define SUBMETA(external_name, ... /*meta_expression*/) CUSTOM_META((), xxsubmeta, external_name, __VA_ARGS__)

namespace eightrefl
{

struct EIGHTREFL_API meta_t
{
    std::string const name;
    std::any value;
    attribute_t<meta_t> meta;
};

} // namespace eightrefl

#endif // EIGHTREFL_META_HPP
