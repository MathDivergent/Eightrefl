#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/tuple.hpp>

TEST(TestBuiltin, TestTuple)
{
    eightrefl::reflectable<std::tuple<int, float, bool>>();

    auto type = eightrefl::standard()->find("std::tuple<int, float, bool>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::tuple<int, float, bool>");
    EXPECT("type-size", type->size == sizeof(std::tuple<int, float, bool>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::tuple<int, float, bool>()") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::tuple<int, float, bool>(std::tuple<int, float, bool> const&)") != nullptr);
    EXPECT("factory-R(Args...)", type->factory.find("std::tuple<int, float, bool>(int, float, bool)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
