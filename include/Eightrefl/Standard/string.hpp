#ifndef EIGHTREFL_STANDARD_STRING_HPP
#define EIGHTREFL_STANDARD_STRING_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <string> // basic_string

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// default allocator for basic_string
#include <Eightrefl/Standard/allocator.hpp>

#ifdef EIGHTREFL_FULLY_ENABLE
// as function argument type
#include <Eightrefl/Standard/initializer_list.hpp>
#include <Eightrefl/Standard/iterator.hpp>
#endif // EIGHTREFL_FULLY_ENABLE

// as traits type
#include <Eightrefl/Standard/char_traits.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename CharType, typename TraitsType, typename AllocatorType>),
    (std::basic_string<CharType, TraitsType, AllocatorType>),
    std::basic_string<eightrefl::clean_of<CharType>, eightrefl::clean_of<TraitsType>, eightrefl::clean_of<AllocatorType>>
)

REFLECTABLE_DECLARATION(std::string)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(std::wstring)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()

#ifdef EIGHTREFL_FULLY_ENABLE
#if __cplusplus >= 202002L
REFLECTABLE_DECLARATION(std::u8string)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()
#endif // if

REFLECTABLE_DECLARATION(std::u16string)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE_DECLARATION(std::u32string)
    REFLECTABLE_REGISTRY(eightrefl::standard())
REFLECTABLE_DECLARATION_INIT()
#endif // EIGHTREFL_FULLY_ENABLE

TEMPLATE_REFLECTABLE_DECLARATION(template <typename CharType>, std::basic_string<CharType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::basic_string<" + eightrefl::name_of<CharType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION((template <typename CharType, typename TraitsType>), std::basic_string<CharType, TraitsType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::basic_string<" + eightrefl::name_of<CharType>() + ", " + eightrefl::name_of<TraitsType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename CharType, typename TraitsType, typename AllocatorType>),
    std::basic_string<CharType, TraitsType, AllocatorType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::basic_string<" + eightrefl::name_of<CharType>() + ", " + eightrefl::name_of<TraitsType>() + ", " + eightrefl::name_of<AllocatorType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE
(
    (template <typename CharType, typename TraitsType, typename AllocatorType>),
    std::basic_string<CharType, TraitsType, AllocatorType>
)
    FACTORY(R())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::value_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::value_type))
    FACTORY(R(R const&, typename R::size_type, typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(R const&, typename R::size_type, typename R::size_type))
    FACTORY(R(typename R::value_type const*, typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::value_type const*, typename R::size_type))
    FACTORY(R(typename R::value_type const*, typename R::allocator_type const&))
    FACTORY(R(typename R::value_type const*))
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
    FUNCTION(operator=, R&(typename R::value_type const*))
    FUNCTION(operator=, R&(typename R::value_type))
    FUNCTION(operator=, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(assign, R&(typename R::size_type, typename R::value_type))
    FUNCTION(assign, R&(R const&))
    FUNCTION(assign, R&(R const&, typename R::size_type, typename R::size_type))
    FUNCTION(assign, R&(typename R::value_type const*, typename R::size_type))
    FUNCTION(assign, R&(typename R::value_type const*))
    FUNCTION(assign, R&(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(assign, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(get_allocator)
    FUNCTION(at, typename R::reference(typename R::size_type))
    FUNCTION(at, typename R::const_reference(typename R::size_type) const)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(operator[], typename R::reference(typename R::size_type))
    FUNCTION(operator[], typename R::const_reference(typename R::size_type) const)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(front, typename R::reference())
    FUNCTION(front, typename R::const_reference() const)
    FUNCTION(back, typename R::reference())
    FUNCTION(back, typename R::const_reference() const)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(data, typename R::value_type const*() const)

#if __cplusplus >= 201703L
    FUNCTION(data, typename R::value_type*())
#endif // if

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(c_str)
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
    FUNCTION(length)
    FUNCTION(max_size)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(reserve, void(typename R::size_type))
    FUNCTION(capacity)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(shrink_to_fit)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(insert, R&(typename R::size_type, typename R::size_type, typename R::value_type))
    FUNCTION(insert, R&(typename R::size_type, typename R::value_type const*))
    FUNCTION(insert, R&(typename R::size_type, typename R::value_type const*, typename R::size_type))
    FUNCTION(insert, R&(typename R::size_type, R const&))
    FUNCTION(insert, R&(typename R::size_type, R const&, typename R::size_type, typename R::size_type))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::value_type))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::size_type, typename R::value_type))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(erase, R&(typename R::size_type, typename R::size_type))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(push_back)
    FUNCTION(pop_back)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(append, R&(typename R::size_type, typename R::value_type))
    FUNCTION(append, R&(R const&))
    FUNCTION(append, R&(R const&, typename R::size_type, typename R::size_type))
    FUNCTION(append, R&(typename R::value_type const*, typename R::size_type))
    FUNCTION(append, R&(typename R::value_type const*))
    FUNCTION(append, R&(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(append, R&(std::initializer_list<typename R::value_type>))
    FUNCTION(operator+=, R&(R const&))
    FUNCTION(operator+=, R&(typename R::value_type))
    FUNCTION(operator+=, R&(typename R::value_type const*))
    FUNCTION(operator+=, R&(std::initializer_list<typename R::value_type>))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, R const&))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, R const&, typename R::size_type, typename R::size_type))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, typename R::value_type const*, typename R::size_type))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, typename R::value_type const*, typename R::size_type))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, typename R::value_type const*))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, typename R::value_type const*))
    FUNCTION(replace, R&(typename R::size_type, typename R::size_type, typename R::size_type, typename R::value_type))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::value_type))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(replace, R&(std_const_iterator<R>, std_const_iterator<R>, std::initializer_list<typename R::value_type>))
    FUNCTION(copy)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(resize, void(typename R::size_type))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(resize, void(typename R::size_type, typename R::value_type))
    FUNCTION(swap)
    #endif // EIGHTREFL_FULLY_ENABLE
    
    FUNCTION(find, typename R::size_type(R const&, typename R::size_type) const)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(find, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(rfind, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_first_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_first_not_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_last_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(R const&, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(typename R::value_type const*, typename R::size_type) const)
    FUNCTION(find_last_not_of, typename R::size_type(typename R::value_type, typename R::size_type) const)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(compare, int(R const&) const)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, R const&) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, R const&, typename R::size_type, typename R::size_type) const)
    FUNCTION(compare, int(typename R::value_type const*) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, typename R::value_type const*) const)
    FUNCTION(compare, int(typename R::size_type, typename R::size_type, typename R::value_type const*, typename R::size_type) const)
    #endif // EIGHTREFL_FULLY_ENABLE

#if __cplusplus >= 202002L
    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(starts_with, bool(typename R::value_type) const)
    FUNCTION(starts_with, bool(typename R::value_type const*) const)
    FUNCTION(ends_with, bool(typename R::value_type) const)
    FUNCTION(ends_with, bool(typename R::value_type const*) const)
    #endif // EIGHTREFL_FULLY_ENABLE
#endif // if

    FUNCTION(substr, R(typename R::size_type, typename R::size_type) const)
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_STRING_HPP
