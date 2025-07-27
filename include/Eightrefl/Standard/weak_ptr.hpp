#ifndef EIGHTREFL_STANDARD_WEAK_PTR_HPP
#define EIGHTREFL_STANDARD_WEAK_PTR_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <memory> // weak_ptr

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// as function argument/return type
#include <Eightrefl/Standard/shared_ptr.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ElementType>,
    std::weak_ptr<ElementType>, std::weak_ptr<eightrefl::clean_of<ElementType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ElementType>, std::weak_ptr<ElementType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::weak_ptr<" + eightrefl::name_of<ElementType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ElementType>, std::weak_ptr<ElementType>)
    FACTORY(R())
    FACTORY(R(R const&))
    FACTORY(R(std::shared_ptr<typename R::element_type> const&))
    FUNCTION(operator=, R&(R const&))
    FUNCTION(operator=, R&(std::shared_ptr<typename R::element_type> const&))
    FUNCTION(reset)

    #ifdef EIGHTREFL_FULLY_ENABLE
//  FUNCTION(swap)
    FUNCTION(use_count)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(expired)
    FUNCTION(lock)

    #ifdef EIGHTREFL_FULLY_ENABLE
//  FUNCTION(owner_before, bool(R const&) const)
//  FUNCTION(owner_before, bool(std::shared_ptr<typename R::element_type> const&) const)
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_WEAK_PTR_HPP
