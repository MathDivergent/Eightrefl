#ifndef EIGHTREFL_DELETER_HPP
#define EIGHTREFL_DELETER_HPP

#include <string> // string
#include <any> // any, any_cast
#include <functional> // function

#include <Eightrefl/Attribute.hpp>
#include <Eightrefl/Meta.hpp>

#include <Eightrefl/Traits/Deleter.hpp>

#define DELETER(... /*reflectable_function_type*/) \
    { \
        auto xxdeleter = eightrefl::find_or_add_deleter<CleanR, __VA_ARGS__>(xxtype, injection); \
        xxmeta = &xxdeleter->meta; \
    }


namespace eightrefl
{

struct EIGHTREFL_API deleter_t
{
    std::string const name{};
    std::function<void(std::any const& outer_context)> const call = nullptr;
    attribute_t<meta_t> meta{};
};

template <typename ReflectableType>
auto handler_deleter_call(void(*)(ReflectableType*))
{
    return [](std::any const& outer_context)
    {
        std::any_cast<ReflectableType*>(outer_context)->~ReflectableType();
    };
}

template <typename CustomDeleterType, typename ReflectableType>
auto handler_deleter_call(CustomDeleterType(*)(ReflectableType*))
{
    return [](std::any const& outer_context)
    {
        CustomDeleterType(std::any_cast<ReflectableType*>(outer_context));
    };
}

} // namespace eightrefl

#endif // EIGHTREFL_DELETER_HPP
