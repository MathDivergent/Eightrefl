#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/reference_wrapper.hpp>

TEST(TestBuiltin, TestReferenceWrapper)
{
    eightrefl::reflectable<std::reference_wrapper<int>>();

    auto type = eightrefl::standard()->find("std::reference_wrapper<int>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::reference_wrapper<int>");
    EXPECT("type-size", type->size == sizeof(std::reference_wrapper<int>));
    EXPECT("type-context", type->context != nullptr);

    auto reflection = type->reflection;

    ASSERT("reflection", reflection != nullptr);
    EXPECT("reflection-name", reflection->name == "std::reference_wrapper<int>");

    EXPECT("factory-R(value_type&)", reflection->factory.find("std::reference_wrapper<int>(int&)") != nullptr);
    EXPECT("factory-R(R const&)", reflection->factory.find("std::reference_wrapper<int>(std::reference_wrapper<int> const&)") != nullptr);

    EXPECT("function-operator=", reflection->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-operator value_type&", reflection->function.find("operator int&") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-get", reflection->function.find("get") != nullptr);
}
