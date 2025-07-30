#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/pair.hpp>

TEST(TestStandard, TestPair)
{
    eightrefl::reflectable<std::pair<int, float>>();

    auto type = eightrefl::standard()->find("std::pair<int, float>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::pair<int, float>");
    EXPECT("type-size", type->size == sizeof(std::pair<int, float>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::pair<int, float>()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("factory-R(first_type const&, second_type const&)", type->factory.find("std::pair<int, float>(int const&, float const&)") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::pair<int, float>(std::pair<int, float> const&)") != nullptr);
    EXPECT("function-operator=", type->function.find("operator=") != nullptr);
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("property-first", type->property.find("first") != nullptr);
    EXPECT("property-second", type->property.find("second") != nullptr);
}
#endif // EIGHTREFL_STANDARD_ENABLE
