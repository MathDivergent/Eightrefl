#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/variant.hpp>

TEST(TestBuiltin, TestVariant)
{
    eightrefl::reflectable<std::variant<int, float, bool>>();

    auto type = eightrefl::standard()->find("std::variant<int, float, bool>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::variant<int, float, bool>");
    EXPECT("type-size", type->size == sizeof(std::variant<int, float, bool>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::variant<int, float, bool>()") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::variant<int, float, bool>(std::variant<int, float, bool> const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);
    EXPECT("function-index", type->function.find("index") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-valueless_by_exception", type->function.find("valueless_by_exception") != nullptr);
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
