#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/unique_ptr.hpp>

TEST(TestBuiltin, TestUniquePtr)
{
    eightrefl::reflectable<std::unique_ptr<int>>();

    auto type = eightrefl::standard()->find("std::unique_ptr<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::unique_ptr<int>");
    EXPECT("type-size", type->size == sizeof(std::unique_ptr<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::unique_ptr<int>");

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);
    EXPECT("function-release", reflection->function.find("release") != nullptr);
    EXPECT("function-reset", reflection->function.find("reset") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-get", reflection->function.find("get") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-get_deleter", reflection->function.find("get_deleter") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator bool", reflection->function.find("operator bool") != nullptr);
    EXPECT("function-operator*", reflection->function.find("operator*") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-operator->", reflection->function.find("operator->") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
