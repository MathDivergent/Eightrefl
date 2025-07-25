#ifndef EIGHTREFL_STANDARD_ITERATOR_HPP
#define EIGHTREFL_STANDARD_ITERATOR_HPP

#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Reflectable.hpp>

#include <Eightrefl/Standard/Standard.hpp>

#ifdef EIGHTREFL_FULLY_ENABLE
TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_const_iterator,
    std_const_iterator<StdContainerType>, typename eightrefl::clean_of<StdContainerType>::const_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_const_iterator<StdContainerType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME(eightrefl::name_of<StdContainerType>() + "::const_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_const_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_iterator,
    std_iterator<StdContainerType>, typename eightrefl::clean_of<StdContainerType>::iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_iterator<StdContainerType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME(eightrefl::name_of<StdContainerType>() + "::iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_const_reverse_iterator,
    std_const_reverse_iterator<StdContainerType>, typename eightrefl::clean_of<StdContainerType>::const_reverse_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_const_reverse_iterator<StdContainerType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME(eightrefl::name_of<StdContainerType>() + "::const_reverse_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_const_reverse_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_reverse_iterator,
    std_reverse_iterator<StdContainerType>, typename eightrefl::clean_of<StdContainerType>::reverse_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_reverse_iterator<StdContainerType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME(eightrefl::name_of<StdContainerType>() + "::reverse_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_reverse_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_const_local_iterator,
    std_const_local_iterator<StdContainerType>, typename eightrefl::clean_of<StdContainerType>::const_local_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_const_local_iterator<StdContainerType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME(eightrefl::name_of<StdContainerType>() + "::const_local_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_const_local_iterator<StdContainerType>)
REFLECTABLE_INIT()


TEMPLATE_REFLECTABLE_USING
(
    template <class StdContainerType>, std_local_iterator,
    std_local_iterator<StdContainerType>, typename eightrefl::clean_of<StdContainerType>::local_iterator
)

TEMPLATE_REFLECTABLE_DECLARATION(template <class StdContainerType>, std_local_iterator<StdContainerType>)
    REFLECTABLE_REGISTRY(eightrefl::standard())
    REFLECTABLE_NAME(eightrefl::name_of<StdContainerType>() + "::local_iterator")
REFLECTABLE_DECLARATION_INIT()

TEMPLATE_REFLECTABLE(template <class StdContainerType>, std_local_iterator<StdContainerType>)
REFLECTABLE_INIT()
#endif // EIGHTREFL_FULLY_ENABLE
#endif // EIGHTREFL_STANDARD_ENABLE

#endif // EIGHTREFL_STANDARD_ITERATOR_HPP
