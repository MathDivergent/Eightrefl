#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Dev/Registry.hpp>
#include <Eightrefl/Dev/Type.hpp>

#include <Eightrefl/Standard/string.hpp>

#ifdef EIGHTREFL_RTTI_ENABLE
#include <Eightrefl/Standard/typeindex.hpp>
#endif // EIGHTREFL_RTTI_ENABLE

#include <Eightrefl/Standard/unordered_map.hpp>

REFLECTABLE(eightrefl::registry_t)
    FACTORY(eightrefl::registry_t())
    FUNCTION(find, eightrefl::type_t*(std::string const&) const)

    #ifdef EIGHTREFL_RTTI_ENABLE
    FUNCTION(find, eightrefl::type_t*(std::type_index) const)
    #endif // EIGHTREFL_RTTI_ENABLE

    PROPERTY(all)

    #ifdef EIGHTREFL_RTTI_ENABLE
    PROPERTY(rtti_all)
    #endif // EIGHTREFL_RTTI_ENABLE
REFLECTABLE_INIT()
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE
