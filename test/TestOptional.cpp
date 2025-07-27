#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/optional.hpp>

TEST(TestBuiltin, TestNulloptT)
{
    auto type = eightrefl::standard()->find("std::nullopt_t");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::nullopt_t");
    EXPECT("type-size", type->size == sizeof(std::nullopt_t));
    EXPECT("type-context", type->context != nullptr);
}

TEST(TestBuiltin, TestOptional)
{
    eightrefl::reflectable<std::optional<int>>();

    auto type = eightrefl::standard()->find("std::optional<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::optional<int>");
    EXPECT("type-size", type->size == sizeof(std::optional<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::optional<int>()") != nullptr);
    EXPECT("factory-R(std::nullopt_t)", type->factory.find("std::optional<int>(std::nullopt_t)") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::optional<int>(std::optional<int> const&)") != nullptr);
    EXPECT("factory-R(value_type const&)", type->factory.find("std::optional<int>(int const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-operator->", type->function.find("operator->") != nullptr);
    EXPECT("function-operator*", type->function.find("operator*") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator bool", type->function.find("operator bool") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
//  EXPECT("function-has_value", type->function.find("has_value") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-value", type->function.find("value") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-value_or", type->function.find("value_or") != nullptr);
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

//  EXPECT("function-reset", type->function.find("reset") != nullptr);
    EXPECT("function-emplace", type->function.find("emplace") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
