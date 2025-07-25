#ifndef EIGHTREFL_STANDARD_FORWARD_LIST_HPP
#define EIGHTREFL_STANDARD_FORWARD_LIST_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <forward_list> // forward_list

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// default allocator for forward_list
#include <Eightrefl/Standard/allocator.hpp>

#ifdef EIGHTREFL_FULLY_ENABLE
// as function argument type
#include <Eightrefl/Standard/initializer_list.hpp>
#include <Eightrefl/Standard/function.hpp>
#include <Eightrefl/Standard/iterator.hpp>
#endif // EIGHTREFL_FULLY_ENABLE

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, typename AllocatorType>),
    (std::forward_list<ValueType, AllocatorType>), std::forward_list<eightrefl::clean_of<ValueType>, eightrefl::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::forward_list<ValueType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::forward_list<" + eightrefl::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename ValueType, typename AllocatorType>), std::forward_list<ValueType, AllocatorType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::forward_list<" + eightrefl::name_of<ValueType>() + ", " + eightrefl::name_of<AllocatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType, typename AllocatorType>), std::forward_list<ValueType, AllocatorType>)
    FACTORY(R())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::const_reference))
    FACTORY(R(typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>))
    FACTORY(R(R const&, typename R::allocator_type const&))
    #endif // EIGHTREFL_FULLY_ENABLE

    FACTORY(R(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(operator=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(assign, void(typename R::size_type, typename R::const_reference))
    FUNCTION(assign, void(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(assign, void(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(front, typename R::reference())
    FUNCTION(before_begin, std_const_iterator<R>() const)
    FUNCTION(before_begin, std_iterator<R>())
    FUNCTION(cbefore_begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_iterator<R>())
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(end, std_iterator<R>())
    FUNCTION(cend, std_const_iterator<R>() const)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(empty)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(max_size)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(insert_after, std_iterator<R>(std_const_iterator<R>, typename R::const_reference))
    FUNCTION(insert_after, std_iterator<R>(std_const_iterator<R>, typename R::size_type, typename R::const_reference))
    FUNCTION(insert_after, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert_after, std_iterator<R>(std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(erase_after, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase_after, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(push_front, void(typename R::const_reference))
    FUNCTION(pop_front)
    FUNCTION(resize, void(typename R::size_type))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(resize, void(typename R::size_type, typename R::const_reference))
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(merge, void(R&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(merge, void(R&, std::function<bool(typename R::const_reference, typename R::const_reference)>))
    FUNCTION(splice_after, void(std_const_iterator<R>, R&))
    FUNCTION(splice_after, void(std_const_iterator<R>, R&, std_const_iterator<R>))
    FUNCTION(splice_after, void(std_const_iterator<R>, R&, std_const_iterator<R>, std_const_iterator<R>))
    #endif // EIGHTREFL_FULLY_ENABLE

#if __cplusplus < 202002L
    FUNCTION(remove, void(typename R::const_reference))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(remove_if, void(std::function<bool(typename R::const_reference)>))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(unique, void())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(unique, void(std::function<bool(typename R::const_reference, typename R::const_reference)>))
    #endif // EIGHTREFL_FULLY_ENABLE
#else
    FUNCTION(remove, typename R::size_type(typename R::const_reference))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(remove_if, typename R::size_type(std::function<bool(typename R::const_reference)>))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(unique, typename R::size_type())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(unique, typename R::size_type(std::function<bool(typename R::const_reference, typename R::const_reference)>))
    #endif // EIGHTREFL_FULLY_ENABLE
#endif // if

    FUNCTION(reverse)
    FUNCTION(sort, void())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(sort, void(std::function<bool(typename R::const_reference, typename R::const_reference)>))
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_FORWARD_LIST_HPP
