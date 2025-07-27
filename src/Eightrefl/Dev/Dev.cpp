#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
#include <Eightrefl/Dev/Dev.hpp>

#include <Eightrefl/Registry.hpp>

namespace eightrefl
{

registry_t* dev()
{
    static registry_t self; return &self;
}

} // namespace eightrefl
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE
