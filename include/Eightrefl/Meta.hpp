#ifndef EIGHTREFL_META_HPP
#define EIGHTREFL_META_HPP

#include <string> // string
#include <any> // any

#include <Eightrefl/Attribute.hpp>

#include <Eightrefl/Detail/Meta.hpp>
#include <Eightrefl/Detail/Macro.hpp> // EIGHTREFL_DEPAREN

#define META(external_name, ... /*meta_expression*/) \
    { \
        eightrefl::find_or_add_meta<CleanR>(*xxmeta, external_name __VA_OPT__(, __VA_ARGS__), injection); \
    }


namespace eightrefl
{

struct EIGHTREFL_API meta_t
{
    std::string const name{};
    std::any value{};
};

} // namespace eightrefl

#endif // EIGHTREFL_META_HPP
