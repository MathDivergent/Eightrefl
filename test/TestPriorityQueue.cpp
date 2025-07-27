#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/priority_queue.hpp>

TEST(TestBuiltin, TestPriorityQueue)
{
    eightrefl::reflectable<std::priority_queue<int>>();

    auto type = eightrefl::standard()->find("std::priority_queue<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::priority_queue<int>");
    EXPECT("type-size", type->size == sizeof(std::priority_queue<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::priority_queue<int>()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(value_compare const&, container_type const&)", type->factory.find("std::priority_queue<int>(std::less<int> const&, std::vector<int> const&)") != nullptr);
    EXPECT("factory-R(value_compare const&)", type->factory.find("std::priority_queue<int>(std::less<int> const&)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(R const&)", type->factory.find("std::priority_queue<int>(std::priority_queue<int> const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);
    EXPECT("function-top", type->function.find("top") != nullptr);
    EXPECT("function-empty", type->function.find("empty") != nullptr);
    EXPECT("function-size", type->function.find("size") != nullptr);
    EXPECT("function-push", type->function.find("push") != nullptr);
    EXPECT("function-pop", type->function.find("pop") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
