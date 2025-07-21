#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/stack.hpp>

TEST(TestBuiltin, TestStack)
{
    eightrefl::reflectable<std::stack<int>>();

    auto type = eightrefl::standard()->find("std::stack<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::stack<int>");
    EXPECT("type-size", type->size == sizeof(std::stack<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::stack<int>");

    EXPECT("factory-R()", reflection->factory.find("std::stack<int>()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(container_type const&)", reflection->factory.find("std::stack<int>(std::deque<int> const&)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(R const&)", reflection->factory.find("std::stack<int>(std::stack<int> const&)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);
    EXPECT("function-top", reflection->function.find("top") != nullptr);
    EXPECT("function-empty", reflection->function.find("empty") != nullptr);
    EXPECT("function-size", reflection->function.find("size") != nullptr);
    EXPECT("function-push", reflection->function.find("push") != nullptr);
    EXPECT("function-pop", reflection->function.find("pop") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", reflection->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
