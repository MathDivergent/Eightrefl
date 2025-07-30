#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/reference_wrapper.hpp>

TEST(TestStandard, TestReferenceWrapper)
{
    eightrefl::reflectable<std::reference_wrapper<int>>();

    auto type = eightrefl::standard()->find("std::reference_wrapper<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::reference_wrapper<int>");
    EXPECT("type-size", type->size == sizeof(std::reference_wrapper<int>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R(value_type&)", type->factory.find("std::reference_wrapper<int>(int&)") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::reference_wrapper<int>(std::reference_wrapper<int> const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-operator value_type&", type->function.find("operator int&") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-get", type->function.find("get") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
