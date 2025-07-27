#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/initializer_list.hpp>

TEST(TestBuiltin, TestInitializerList)
{
    eightrefl::reflectable<std::initializer_list<int>>();

    auto type = eightrefl::standard()->find("std::initializer_list<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::initializer_list<int>");
    EXPECT("type-size", type->size == sizeof(std::initializer_list<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::initializer_list<int>()") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::initializer_list<int>(std::initializer_list<int> const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-begin", type->function.find("begin") != nullptr);
    EXPECT("function-end", type->function.find("end") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-size", type->function.find("size") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
