#ifndef EIGHTREFL_DELETER_HPP
#define EIGHTREFL_DELETER_HPP

#include <string> // string
#include <any> // any
#include <functional> // function

#include <Eightrefl/Attribute.hpp>
#include <Eightrefl/Utility.hpp>

// .deleter<R, function_type>()
#define DELETER(... /*function_type*/) \
    { \
        using xxtraits = eightrefl::meta::deleter_traits<__VA_ARGS__>; \
        auto xxdeleter = eightrefl::find_or_add_deleter<typename xxtraits::dirty_pointer>(xxtype); \
        injection.template deleter<CleanR, typename xxtraits::pointer>(*xxdeleter); \
        xxmeta = &xxdeleter->meta; \
    }

namespace eightrefl
{

struct meta_t;

struct EIGHTREFL_API deleter_t
{
    std::string const name;
    std::function<void(std::any const& context)> const call = nullptr;
    attribute_t<meta_t> meta;
};

template <typename ReflectableType>
auto handler_deleter_call(void(*)(ReflectableType*))
{
    return [](std::any const& context)
    {
        std::any_cast<ReflectableType*>(context)->~ReflectableType();
    };
}

template <typename CustomDeleterType, typename ReflectableType>
auto handler_deleter_call(CustomDeleterType(*)(ReflectableType*))
{
    return [](std::any const& context)
    {
        CustomDeleterType(std::any_cast<ReflectableType*>(context));
    };
}

} // namespace eightrefl

#endif // EIGHTREFL_DELETER_HPP
