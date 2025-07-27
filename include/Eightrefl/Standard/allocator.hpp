#ifndef EIGHTREFL_STANDARD_ALLOCATOR_HPP
#define EIGHTREFL_STANDARD_ALLOCATOR_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <memory> // allocator

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    template <typename ValueType>,
    std::allocator<ValueType>, std::allocator<eightrefl::clean_of<ValueType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::allocator<ValueType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::allocator<" + eightrefl::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <typename ValueType>, std::allocator<ValueType>)
    FACTORY(R())
    FACTORY(R(R const&))
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_ALLOCATOR_HPP
