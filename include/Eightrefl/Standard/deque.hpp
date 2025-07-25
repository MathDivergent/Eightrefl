#ifndef EIGHTREFL_STANDARD_DEQUE_HPP
#define EIGHTREFL_STANDARD_DEQUE_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <deque> // deque

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// default allocator for deque
#include <Eightrefl/Standard/allocator.hpp>

#ifndef RWW_CORE_MINIMAL
// as function argument type
#include <Eightrefl/Standard/initializer_list.hpp>
#include <Eightrefl/Standard/iterator.hpp>
#endif // EIGHTREFL_FULLY_ENABLE

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename ValueType, typename AllocatorType>),
    (std::deque<ValueType, AllocatorType>), std::deque<eightrefl::clean_of<ValueType>, eightrefl::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename ValueType>, std::deque<ValueType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::deque<" + eightrefl::name_of<ValueType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename ValueType, typename AllocatorType>), std::deque<ValueType, AllocatorType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::deque<" + eightrefl::name_of<ValueType>() + ", " + eightrefl::name_of<AllocatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE((template <typename ValueType, typename AllocatorType>), std::deque<ValueType, AllocatorType>)
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
//  FUNCTION(assign, void(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(assign, void(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(at, typename R::const_reference(typename R::size_type) const)
    FUNCTION(at, typename R::reference(typename R::size_type))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator[], typename R::const_reference(typename R::size_type) const)
    FUNCTION(operator[], typename R::reference(typename R::size_type))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(front, typename R::reference())
    FUNCTION(back, typename R::const_reference() const)
    FUNCTION(back, typename R::reference())
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_iterator<R>())
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(end, std_iterator<R>())
    FUNCTION(cend, std_const_iterator<R>() const)
    FUNCTION(rbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(rbegin, std_reverse_iterator<R>())
    FUNCTION(crbegin, std_const_reverse_iterator<R>() const)
    FUNCTION(rend, std_const_reverse_iterator<R>() const)
    FUNCTION(rend, std_reverse_iterator<R>())
    FUNCTION(crend, std_const_reverse_iterator<R>() const)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(empty)
    FUNCTION(size)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(max_size)
    FUNCTION(shrink_to_fit)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::size_type, typename R::const_reference))
//  FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(push_back, void(typename R::const_reference))
    FUNCTION(push_front, void(typename R::const_reference))
    FUNCTION(pop_back)
    FUNCTION(pop_front)
    FUNCTION(resize, void(typename R::size_type))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(resize, void(typename R::size_type, typename R::const_reference))
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_DEQUE_HPP
