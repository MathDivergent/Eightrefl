#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/allocator.hpp>

TEST(TestBuiltin, TestAllocator)
{
    eightrefl::reflectable<std::allocator<int>>();

    auto type = eightrefl::standard()->find("std::allocator<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::allocator<int>");
    EXPECT("type-size", type->size == sizeof(std::allocator<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::allocator<int>()") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::allocator<int>(std::allocator<int> const&)") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
