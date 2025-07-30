#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/unique_ptr.hpp>

TEST(TestStandard, TestUniquePtr)
{
    eightrefl::reflectable<std::unique_ptr<int>>();

    auto type = eightrefl::standard()->find("std::unique_ptr<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::unique_ptr<int>");
    EXPECT("type-size", type->size == sizeof(std::unique_ptr<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);
    EXPECT("function-release", type->function.find("release") != nullptr);
    EXPECT("function-reset", type->function.find("reset") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-get", type->function.find("get") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-get_deleter", type->function.find("get_deleter") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator bool", type->function.find("operator bool") != nullptr);
    EXPECT("function-operator*", type->function.find("operator*") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-operator->", type->function.find("operator->") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
