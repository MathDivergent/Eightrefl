#ifndef EIGHTREFL_STANDARD_UNIQUE_PTR_HPP
#define EIGHTREFL_STANDARD_UNIQUE_PTR_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <memory> // unique_ptr

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ElementType, typename DeleterType>),
    (std::unique_ptr<ElementType, DeleterType>), std::unique_ptr<eightrefl::clean_of<ElementType>, eightrefl::clean_of<DeleterType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ElementType>, std::default_delete<ElementType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::default_delete<" + eightrefl::name_of<ElementType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ElementType>, std::default_delete<ElementType>)
REFLECTABLE_INIT()

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ElementType>, std::unique_ptr<ElementType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::unique_ptr<" + eightrefl::name_of<ElementType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ElementType, typename DeleterType>),
    std::unique_ptr<ElementType, DeleterType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::unique_ptr<" + eightrefl::name_of<ElementType>() + ", " + eightrefl::name_of<DeleterType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename ElementType, typename DeleterType>),
    std::unique_ptr<ElementType, DeleterType>
)
    FUNCTION(operator=, R&(std::nullptr_t))
    FUNCTION(release)
    FUNCTION(reset, void(typename R::pointer))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(get)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(get_deleter, typename R::deleter_type&())
    FUNCTION(get_deleter, typename R::deleter_type const&() const)
    #endif // REM_CORE_MINIMAL

    FUNCTION(operator bool)
    FUNCTION(operator*)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator->)
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_UNIQUE_PTR_HPP
