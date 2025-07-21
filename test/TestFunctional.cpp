#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/functional.hpp>

TEST(TestBuiltin::TestFunctional, TestHash)
{
    eightrefl::reflectable<std::hash<int>>();

    auto type = eightrefl::standard()->find("std::hash<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::hash<int>");
    EXPECT("type-size", type->size == sizeof(std::hash<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::hash<int>");

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R()", reflection->factory.find("std::hash<int>()") != nullptr);
    EXPECT("factory-R(std::nullptr_t)", reflection->factory.find("std::hash<int>(std::hash<int> const&)") != nullptr);
    EXPECT("function-operator()", reflection->function.find("operator()") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}

TEST(TestBuiltin::TestFunctional, TestEqualTo)
{
    eightrefl::reflectable<std::equal_to<int>>();

    auto type = eightrefl::standard()->find("std::equal_to<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::equal_to<int>");
    EXPECT("type-size", type->size == sizeof(std::equal_to<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::equal_to<int>");
}

TEST(TestBuiltin::TestFunctional, TestLess)
{
    eightrefl::reflectable<std::less<int>>();

    auto type = eightrefl::standard()->find("std::less<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::less<int>");
    EXPECT("type-size", type->size == sizeof(std::less<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::less<int>");
}

TEST(TestBuiltin::TestFunctional, TestGreater)
{
    eightrefl::reflectable<std::greater<int>>();

    auto type = eightrefl::standard()->find("std::greater<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::greater<int>");
    EXPECT("type-size", type->size == sizeof(std::greater<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::greater<int>");
}
