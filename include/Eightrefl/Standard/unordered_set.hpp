#ifndef EIGHTREFL_STANDARD_UNORDERED_SET_HPP
#define EIGHTREFL_STANDARD_UNORDERED_SET_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <unordered_set> // unordered_set, unordered_multiset

#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/BuiltIn/Core.hpp>

// default allocator for unordered_set, unordered_multiset
#include <Eightrefl/Standard/allocator.hpp>

#ifdef EIGHTREFL_FULLY_ENABLE
// as function argument/result type
#include <Eightrefl/Standard/initializer_list.hpp>
#include <Eightrefl/Standard/iterator.hpp>
#include <Eightrefl/Standard/pair.hpp>
#endif // EIGHTREFL_FULLY_ENABLE

// hash - as hasher
// equal_to - as comparator
#include <Eightrefl/Standard/functional.hpp>

#include <Eightrefl/Standard/Standard.hpp>

TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename HasherType, typename ComparatorType, typename AllocatorType>),
    (std::unordered_set<KeyType, HasherType, ComparatorType, AllocatorType>),
    std::unordered_set<eightrefl::clean_of<KeyType>, eightrefl::clean_of<HasherType>, eightrefl::clean_of<ComparatorType>, eightrefl::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename KeyType>, std::unordered_set<KeyType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::unordered_set<" + eightrefl::name_of<KeyType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename HasherType>),
    std::unordered_set<KeyType, HasherType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::unordered_set<" + eightrefl::name_of<KeyType>() + ", " + eightrefl::name_of<HasherType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename HasherType, typename ComparatorType>),
    std::unordered_set<KeyType, HasherType, ComparatorType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME
    (
        "std::unordered_set<" + eightrefl::name_of<KeyType>() + ", " + eightrefl::name_of<ComparatorType>() + ", " + eightrefl::name_of<HasherType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename HasherType, typename ComparatorType, typename AllocatorType>),
    std::unordered_set<KeyType, HasherType, ComparatorType, AllocatorType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME
    (
        "std::unordered_set<" + eightrefl::name_of<KeyType>() + ", " + eightrefl::name_of<HasherType>() + ", "
                              + eightrefl::name_of<ComparatorType>() + ", " + eightrefl::name_of<AllocatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()


TEMPLATE_REFLECTABLE_CLEAN
(
    (template <typename KeyType, typename HasherType, typename ComparatorType, typename AllocatorType>),
    (std::unordered_multiset<KeyType, HasherType, ComparatorType, AllocatorType>),
    std::unordered_multiset<eightrefl::clean_of<KeyType>, eightrefl::clean_of<HasherType>, eightrefl::clean_of<ComparatorType>, eightrefl::clean_of<AllocatorType>>
)

TEMPLATE_REFLECTABLE_DECLARATION(template <typename KeyType>, std::unordered_multiset<KeyType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::unordered_multiset<" + eightrefl::name_of<KeyType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename HasherType>),
    std::unordered_multiset<KeyType, HasherType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME("std::unordered_set<" + eightrefl::name_of<KeyType>() + ", " + eightrefl::name_of<HasherType>() + ">")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename HasherType, typename ComparatorType>),
    std::unordered_multiset<KeyType, HasherType, ComparatorType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME
    (
        "std::unordered_multiset<" + eightrefl::name_of<KeyType>() + ", " + eightrefl::name_of<ComparatorType>() + ", " + eightrefl::name_of<HasherType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE_DECLARATION
(
    (template <typename KeyType, typename HasherType, typename ComparatorType, typename AllocatorType>),
    std::unordered_multiset<KeyType, HasherType, ComparatorType, AllocatorType>
)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME
    (
        "std::unordered_multiset<" + eightrefl::name_of<KeyType>() + ", " + eightrefl::name_of<HasherType>() + ", "
                                   + eightrefl::name_of<ComparatorType>() + ", " + eightrefl::name_of<AllocatorType>() + ">"
    )
REFLECTABLE_DECLARATION_INIT()


template <typename> struct xxeightrefl_is_any_std_unordered_set : std::false_type {};

template <typename KeyType, typename HasherType, typename ComparatorType, typename AllocatorType>
struct xxeightrefl_is_any_std_unordered_set<std::unordered_set<KeyType, HasherType, ComparatorType, AllocatorType>> : std::true_type {};

template <typename KeyType, typename HasherType, typename ComparatorType, typename AllocatorType>
struct xxeightrefl_is_any_std_unordered_set<std::unordered_multiset<KeyType, HasherType, ComparatorType, AllocatorType>> : std::true_type {};

CONDITIONAL_REFLECTABLE(xxeightrefl_is_any_std_unordered_set<R>::value)
    FACTORY(R())

    #ifdef EIGHTREFL_FULLY_ENABLE
    FACTORY(R(typename R::size_type, typename R::hasher const&, typename R::key_equal const&, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::hasher const&, typename R::key_equal const&))
    FACTORY(R(typename R::size_type, typename R::hasher const&))
    FACTORY(R(typename R::size_type))
    FACTORY(R(typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(typename R::size_type, typename R::hasher const&, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::allocator_type const&))
    FACTORY(R(std_const_iterator<R>, std_const_iterator<R>, typename R::size_type, typename R::hasher const&, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&, typename R::allocator_type const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&, typename R::key_equal const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type))
    FACTORY(R(std::initializer_list<typename R::value_type>, typename R::size_type, typename R::hasher const&, typename R::allocator_type const&))
    #endif // EIGHTREFL_FULLY_ENABLE

    FACTORY(R(R const&))
    FUNCTION(operator=, R&(R const&))

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(get_allocator)
    FUNCTION(begin, std_const_iterator<R>() const)
    FUNCTION(begin, std_iterator<R>())
    FUNCTION(cbegin, std_const_iterator<R>() const)
    FUNCTION(end, std_const_iterator<R>() const)
    FUNCTION(end, std_iterator<R>())
    FUNCTION(cend, std_const_iterator<R>() const)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(empty)
    FUNCTION(size)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(max_size)
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(clear)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(insert, std::pair<std_iterator<R>, bool>(typename R::const_reference))
    FUNCTION(insert, std_iterator<R>(std_const_iterator<R>, typename R::const_reference))
    FUNCTION(insert, void(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(insert, void(std::initializer_list<typename R::value_type>))
    FUNCTION(erase, std_iterator<R>(std_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>))
    FUNCTION(erase, std_iterator<R>(std_const_iterator<R>, std_const_iterator<R>))
    FUNCTION(swap)
//  FUNCTION(extract, typename R::node_type(std_const_iterator<R>))
//  FUNCTION(extract, typename R::node_type(typename R::key_type const&))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(merge, void(R&))
    FUNCTION(count, typename R::size_type(typename R::key_type const&) const)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(find, std_iterator<R>(typename R::key_type const&))
    FUNCTION(find, std_const_iterator<R>(typename R::key_type const&) const)
    #endif // EIGHTREFL_FULLY_ENABLE

#if __cplusplus >= 202002L
    FUNCTION(contains, bool(typename R::key_type const&) const)
#endif // if

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(equal_range, std::pair<std_iterator<R>, std_iterator<R>>(typename R::key_type const&))
    FUNCTION(equal_range, std::pair<std_const_iterator<R>, std_const_iterator<R>>(typename R::key_type const&) const)
    FUNCTION(begin, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(begin, std_local_iterator<R>(typename R::size_type))
    FUNCTION(cbegin, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(end, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(end, std_local_iterator<R>(typename R::size_type))
    FUNCTION(cend, std_const_local_iterator<R>(typename R::size_type) const)
    FUNCTION(bucket_count)
    FUNCTION(max_bucket_count)
    FUNCTION(bucket_size)
    FUNCTION(bucket, typename R::size_type(typename R::key_type const&) const)
    FUNCTION(load_factor)
    FUNCTION(max_load_factor, float() const)
    FUNCTION(max_load_factor, void(float))
    #endif // EIGHTREFL_FULLY_ENABLE

    FUNCTION(rehash)
    FUNCTION(reserve)

    #ifdef EIGHTREFL_FULLY_ENABLE
    FUNCTION(hash_function)
    FUNCTION(key_eq)
    #endif // EIGHTREFL_FULLY_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_UNORDERED_SET_HPP
