#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/queue.hpp>

TEST(TestBuiltin, TestQueue)
{
    eightrefl::reflectable<std::queue<int>>();

    auto type = eightrefl::standard()->find("std::queue<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::queue<int>");
    EXPECT("type-size", type->size == sizeof(std::queue<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::queue<int>()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(container_type const&)", type->factory.find("std::queue<int>(std::deque<int> const&)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(R const&)", type->factory.find("std::queue<int>(std::queue<int> const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);
    EXPECT("function-front", type->function.find("front") != nullptr);
    EXPECT("function-back", type->function.find("back") != nullptr);
    EXPECT("function-empty", type->function.find("empty") != nullptr);
    EXPECT("function-size", type->function.find("size") != nullptr);
    EXPECT("function-push", type->function.find("push") != nullptr);
    EXPECT("function-pop", type->function.find("pop") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
