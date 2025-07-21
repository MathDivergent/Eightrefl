#include <Eightrefl/Standard/Standard.hpp>

#include <Eightrefl/Registry.hpp>

namespace eightrefl
{

registry_t* standard()
{
    static registry_t self; return &self;
}

} // namespace eightrefl
