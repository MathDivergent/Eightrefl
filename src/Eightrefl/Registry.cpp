#include <Eightrefl/Registry.hpp>
#include <Eightrefl/Type.hpp>

#include <Eightrefl/Injection.hpp>
#include <Eightrefl/Child.hpp>

#include <Eightrefl/Parent.hpp>
#include <Eightrefl/Factory.hpp>
#include <Eightrefl/Function.hpp>
#include <Eightrefl/Property.hpp>
#include <Eightrefl/Deleter.hpp>
#include <Eightrefl/Meta.hpp>

namespace eightrefl
{

registry_t::registry_t()
{
    all.reserve(EIGHTREFL_REGISTRY_RESERVE_SIZE);
}

registry_t::~registry_t()
{
    for (auto& [name, meta] : all) delete meta;
}

type_t* registry_t::find(std::string const& name) const
{
    auto it = all.find(name);
    return it != all.end() ? it->second : nullptr;
}

#ifdef EIGHTREFL_RTTI_ENABLE
type_t* registry_t::find(std::type_index typeindex) const
{
    auto it = rtti_all.find(typeindex);
    return it != rtti_all.end() ? it->second : nullptr;
}
#endif // EIGHTREFL_RTTI_ENABLE

registry_t* global()
{
    static registry_t self; return &self;
}

} // namespace eightrefl
