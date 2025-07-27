#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/weak_ptr.hpp>

TEST(TestBuiltin, TestWseakPtr)
{
    eightrefl::reflectable<std::weak_ptr<int>>();

    auto type = eightrefl::standard()->find("std::weak_ptr<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::weak_ptr<int>");
    EXPECT("type-size", type->size == sizeof(std::weak_ptr<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::weak_ptr<int>()") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::weak_ptr<int>(std::weak_ptr<int> const&)") != nullptr);
    EXPECT("factory-R(std::shared_ptr<element_type> const&)", type->factory.find("std::weak_ptr<int>(std::shared_ptr<int> const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);
    EXPECT("function-reset", type->function.find("reset") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
//  EXPECT("function-swap", type->function.find("swap") != nullptr);
    EXPECT("function-use_count", type->function.find("use_count") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-expired", type->function.find("expired") != nullptr);
    EXPECT("function-lock", type->function.find("lock") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
//  EXPECT("function-owner_before", type->function.find("owner_before") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
