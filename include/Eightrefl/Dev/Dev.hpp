#ifndef EIGHTREFL_DEV_DEV_HPP
#define EIGHTREFL_DEV_DEV_HPP

#ifdef EIGHTREFL_DEV_ENABLE
#ifdef EIGHTREFL_STANDARD_ENABLE
namespace eightrefl
{

struct registry_t;

extern EIGHTREFL_API registry_t* dev();

} // namespace eightrefl
#endif // EIGHTREFL_STANDARD_ENABLE
#endif // EIGHTREFL_DEV_ENABLE

#endif // EIGHTREFL_DEV_DEV_HPP
