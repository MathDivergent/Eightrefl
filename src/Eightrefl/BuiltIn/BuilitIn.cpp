#include <Eightrefl/BuiltIn/BuiltIn.hpp>

#include <Eightrefl/Registry.hpp>

namespace eightrefl
{

registry_t* builtin()
{
    static registry_t self; return &self;
}

} // namespace eightrefl
