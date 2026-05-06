#ifndef EIGHTREFL_REFLECTABLE_DECLARATION_HPP
#define EIGHTREFL_REFLECTABLE_DECLARATION_HPP

#include <Eightrefl/Registry.hpp>

#include <Eightrefl/Traits/ReflectableDeclaration.hpp>
#include <Eightrefl/Traits/Dirty.hpp>

#include <Eightrefl/Detail/Macro.hpp>

#define REFLECTABLE_DECLARATION(... /*reflectable_type*/) \
    template <> struct xxeightrefl_traits<__VA_ARGS__> { \
        using R = typename ::xxeightrefl_dirty_traits<__VA_ARGS__>::R; \
        [[maybe_unused]] static constexpr auto xxnative_name = #__VA_ARGS__;

#define TEMPLATE_REFLECTABLE_DECLARATION(reflectable_type_template_header, ... /*reflectable_type_template*/) \
    EIGHTREFL_DEPAREN(reflectable_type_template_header) struct xxeightrefl_traits<__VA_ARGS__> { \
        using R = typename ::xxeightrefl_dirty_traits<__VA_ARGS__>::R; \
        REFLECTABLE_LAZY_EVALUATE()

#define CONDITIONAL_REFLECTABLE_DECLARATION(... /*reflectable_type_condition*/) \
    template <typename DirtyR> struct xxeightrefl_traits<DirtyR, std::enable_if_t<__VA_ARGS__>> { \
        using R = typename ::xxeightrefl_dirty_traits<DirtyR>::R; \
        REFLECTABLE_LAZY_EVALUATE()


#define REFLECTABLE_REGISTRY(... /*reflectable_registry_pointer*/) \
    static auto registry() { return __VA_ARGS__; }

#define REFLECTABLE_NAME(... /*reflectable_name_string*/) \
    static auto name() { return __VA_ARGS__; }

#define REFLECTABLE_LAZY_EVALUATE() \
    struct xxlazy_evaluate;


#define REFLECTABLE_DECLARATION_INIT() \
    };


#define REFLECTABLE_ACCESS() \
    template <typename, typename> friend struct xxeightrefl;


namespace eightrefl
{

namespace detail
{

template <typename, typename enable = void> struct is_complete : std::false_type {};
template <typename Type> struct is_complete<Type, std::void_t<decltype(sizeof(Type))>> : std::true_type {};

} // namespace detail

struct type_t;

template <typename DirtyReflectableType>
std::string name_of()
{
    using reflectable_traits = ::xxeightrefl_traits<DirtyReflectableType>;

    static_assert
    (
        detail::is_complete<reflectable_traits>::value,
        "name_of: reflection declaration for this type not found"
    );

    if constexpr (::xxeightrefl_traits_has_reflectable_name<DirtyReflectableType>::value)
    {
        return reflectable_traits::name();
    }
    else
    {
        return reflectable_traits::xxnative_name;
    }
}

template <typename DirtyReflectableType>
registry_t* registry_of()
{
    using reflectable_traits = ::xxeightrefl_traits<DirtyReflectableType>;

    static_assert
    (
        detail::is_complete<reflectable_traits>::value,
        "registry_of: reflection declaration for this type not found"
    );

    if constexpr (::xxeightrefl_traits_has_reflectable_registry<DirtyReflectableType>::value)
    {
        return reflectable_traits::registry();
    }
    else
    {
        return global();
    }
}

template <typename DirtyReflectableType>
type_t* type_of()
{
    return registry_of<DirtyReflectableType>()->find(name_of<DirtyReflectableType>());
}

} // namespace eightrefl


#define REFLECTABLE_CLEAN(dirty_type, ... /*clean_reflectable_type*/) \
    template <> struct xxeightrefl_dirty_traits<dirty_type> { using R = __VA_ARGS__; };

#define TEMPLATE_REFLECTABLE_CLEAN(dirty_type_template_header, dirty_type_template, ... /*clean_reflectable_type_template*/) \
    EIGHTREFL_DEPAREN(dirty_type_template_header) struct xxeightrefl_dirty_traits<EIGHTREFL_DEPAREN(dirty_type_template)> { using R = __VA_ARGS__; };


#define REFLECTABLE_DIRTY(dirty_type, ... /*clean_reflectable_type*/) \
    struct dirty_type final : ::xxeightrefl_enable_dirty<__VA_ARGS__> {}; \
    REFLECTABLE_CLEAN(dirty_type, __VA_ARGS__)

#define TEMPLATE_REFLECTABLE_DIRTY(dirty_type_template_header, dirty_type, dirty_type_template, ... /*clean_reflectable_type_template*/) \
    EIGHTREFL_DEPAREN(dirty_type_template_header) struct dirty_type : ::xxeightrefl_enable_dirty<__VA_ARGS__> {}; \
    TEMPLATE_REFLECTABLE_CLEAN(dirty_type_template_header, dirty_type_template, __VA_ARGS__)


namespace eightrefl
{

template <typename DirtyReflectableType>
using clean_of = typename ::xxeightrefl_dirty_traits<DirtyReflectableType>::R;

} // namespace eightrefl

#endif // EIGHTREFL_REFLECTABLE_DECLARATION_HPP
