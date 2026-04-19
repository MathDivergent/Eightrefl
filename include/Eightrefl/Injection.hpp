#ifndef EIGHTREFL_INJECTION_HPP
#define EIGHTREFL_INJECTION_HPP

#include <any> // any
#include <functional> // function

#include <Eightrefl/Attribute.hpp>
#include <Eightrefl/Meta.hpp>
#include <Eightrefl/Utility.hpp>

#include <Eightrefl/Detail/Meta.hpp>

#define INJECTION(... /*reflectable_injection_type*/) \
    { \
        auto xxinjection = ::eightrefl::find_or_add_injection<CleanR, __VA_ARGS__>(xxtype, injection); \
        xxmeta = &xxinjection->meta; \
    }


namespace eightrefl
{

struct type_t;
struct parent_t;
struct factory_t;
struct function_t;
struct property_t;
struct deleter_t;
struct injection_t;

struct EIGHTREFL_API injectable_t
{
    template <typename DirtyReflectableType>
    void type(eightrefl::type_t&) {}

    template <typename ReflectableType, typename DirtyReflectableParentType>
    void parent(eightrefl::parent_t&) {}

    template <typename ReflectableType, typename FunctionTypePointer>
    void factory(eightrefl::factory_t&) {}

    template <typename ReflectableType, typename FunctionTypePointer>
    void function(eightrefl::function_t&) {}

    template <typename ReflectableType, typename ITypePointer, typename OTypePointer>
    void property(eightrefl::property_t&) {}

    template <typename ReflectableType, typename BitfieldType>
    void bitfield(eightrefl::property_t&) {}

    template <typename ReflectableType, typename FunctionTypePointer>
    void deleter(eightrefl::deleter_t&) {}

    template <typename ReflectableType, typename DirtyReflectableInjectionType>
    void injection(eightrefl::injection_t&) {}

    template <typename ReflectableType, typename MetaType>
    void meta(eightrefl::meta_t&) {}
};

struct EIGHTREFL_API injection_t
{
    type_t* const type = nullptr;
    std::function<void(std::any const& injectable_context)> const call = nullptr;
    attribute_t<meta_t> meta{};
};

template <typename ReflectionType, class InjectionType>
auto handler_injection_call()
{
    return [](std::any const& injectable_context)
    {
        ::xxeightrefl<ReflectionType>::evaluate(utility::forward<InjectionType&>(injectable_context));
    };
}

} // namespace eightrefl

#endif // EIGHTREFL_INJECTION_HPP
