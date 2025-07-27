#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/shared_ptr.hpp>

TEST(TestBuiltin, TestSharedPtr)
{
    eightrefl::reflectable<std::shared_ptr<int>>();

    auto type = eightrefl::standard()->find("std::shared_ptr<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::shared_ptr<int>");
    EXPECT("type-size", type->size == sizeof(std::shared_ptr<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::shared_ptr<int>()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(std::nullptr_t)", type->factory.find("std::shared_ptr<int>(std::nullptr_t)") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("factory-R(element_type*)", type->factory.find("std::shared_ptr<int>(int*)") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::shared_ptr<int>(std::shared_ptr<int> const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);
    EXPECT("function-reset", type->function.find("reset") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
//  EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-get", type->function.find("get") != nullptr);
    EXPECT("function-operator*", type->function.find("operator*") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-operator->", type->function.find("operator->") != nullptr);
    EXPECT("function-use_count", type->function.find("use_count") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator bool", type->function.find("operator bool") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
