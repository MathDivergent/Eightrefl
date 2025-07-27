#ifndef EIGHTREFL_ATTRIBUTE_HPP
#define EIGHTREFL_ATTRIBUTE_HPP

#include <string> // string
#include <unordered_map> // unordered_map

namespace eightrefl
{

template <class MetaType>
struct attribute_t
{
    ~attribute_t()
    {
        for (auto const& [key, item] : all) delete item;
    }

    MetaType* find(std::string const& name) const
    {
        auto it = all.find(name);
        if (it == all.end()) return nullptr;

        return it->second;
    }

    MetaType* add(std::string const& name, MetaType const& meta)
    {
        auto item = new MetaType(meta);
        all.emplace(name, item);
        return item;
    }

    std::unordered_map<std::string, MetaType*> all;
};

} // namespace eightrefl

#endif // EIGHTREFL_ATTRIBUTE_HPP
