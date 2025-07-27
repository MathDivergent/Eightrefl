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

    EXPECT("factory-R()", type->factory.find("std::any()") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::any(std::any const&)") != nullptr);

    EXPECT("function-reset", type->function.find("reset") != nullptr);
    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-has_value", type->function.find("has_value") != nullptr);

    #ifdef EIGHTREFL_RTTI_ENABLE
    EXPECT("function-type", type->function.find("type") != nullptr);
    #endif // EIGHTREFL_RTTI_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
