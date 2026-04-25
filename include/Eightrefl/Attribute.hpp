#ifndef EIGHTREFL_ATTRIBUTE_HPP
#define EIGHTREFL_ATTRIBUTE_HPP

#include <string> // string
#include <unordered_map> // unordered_map

#ifndef EIGHTREFL_ATTRIBUTE_RESERVE_SIZE
    #define EIGHTREFL_ATTRIBUTE_RESERVE_SIZE std::size_t(8)
#endif // EIGHTREFL_ATTRIBUTE_RESERVE_SIZE

namespace eightrefl
{

template <class ElementType>
struct attribute_t
{
    attribute_t()
    {
        all.reserve(EIGHTREFL_ATTRIBUTE_RESERVE_SIZE);
    }

    ElementType* find(std::string const& name)
    {
        auto it = all.find(name);
        return it != all.end() ? &it->second : nullptr;
    }

    ElementType* add(std::string const& name, ElementType const& meta)
    {
        return &all.emplace(name, meta).first->second;
    }

    std::unordered_map<std::string, ElementType> all{};
};

} // namespace eightrefl

#endif // EIGHTREFL_ATTRIBUTE_HPP
