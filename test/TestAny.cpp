#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/any.hpp>

TEST(TestBuiltin, TestAny)
{
    auto type = eightrefl::standard()->find("std::any");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::any");
    EXPECT("type-size", type->size == sizeof(std::any));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::any");

    EXPECT("factory-R()", reflection->factory.find("std::any()") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::any(std::any const&)") != nullptr);

    EXPECT("function-reset", reflection->function.find("reset") != nullptr);
    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-has_value", reflection->function.find("has_value") != nullptr);

    #ifdef EIGHTREFL_RTTI_ENABLE
    EXPECT("function-type", reflection->function.find("type") != nullptr);
    #endif // EIGHTREFL_RTTI_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
