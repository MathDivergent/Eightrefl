#ifdef EIGHTREFL_STANDARD_ENABLE
#include <EightreflTestingBase.hpp>

#include <Eightrefl/Standard/function.hpp>

TEST(TestBuiltin, TestFunction)
{
    eightrefl::reflectable<std::function<void(int, float)>>();

    auto type = eightrefl::standard()->find("std::function<void(int, float)>");

    ASSERT("type", type != nullptr);
    EXPECT("type-name", type->name == "std::function<void(int, float)>");
    EXPECT("type-size", type->size == sizeof(std::function<void(int, float)>));
    EXPECT("type-context", type->context != nullptr);

    EXPECT("factory-R()", type->factory.find("std::function<void(int, float)>()") != nullptr);
    EXPECT("factory-R(std::nullptr_t)", type->factory.find("std::function<void(int, float)>(std::nullptr_t)") != nullptr);
    EXPECT("factory-R(R const&)", type->factory.find("std::function<void(int, float)>(std::function<void(int, float)> const&)") != nullptr);

    EXPECT("function-operator=", type->function.find("operator=") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    EXPECT("function-swap", type->function.find("swap") != nullptr);
    #endif // EIGHTREFL_FULLY_ENABLE

    EXPECT("function-operator bool", type->function.find("operator bool") != nullptr);
    EXPECT("function-operator()", type->function.find("operator()") != nullptr);

    #ifdef EIGHTREFL_FULLY_ENABLE
    #ifdef EIGHTREFL_RTTI_ENABLE
    EXPECT("function-target_type", type->function.find("target_type") != nullptr);
    #endif // EIGHTREFL_RTTI_ENABLE
    #endif // EIGHTREFL_FULLY_ENABLE
}
#endif // EIGHTREFL_STANDARD_ENABLE
